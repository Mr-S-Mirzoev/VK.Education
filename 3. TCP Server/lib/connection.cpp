#include "connection.hpp"
#include "exceptions.hpp"

#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <string_view>

namespace tcp {
    Connection::Connection(const Address &addr): _addr(addr) {}
    Connection::Connection(const Address &addr, Descriptor &&d): _addr(addr), _sock(std::move(d)) {}
    Connection::Connection(Connection &&con): _addr(con._addr), _sock(std::move(con._sock)) {}

    Connection& Connection::operator=(Connection &&con) noexcept {
        _addr = con._addr;
        _sock = std::move(con._sock);
        return *this;
    }
  
    void Connection::connect(const Address &addr) {
        struct sockaddr_in copy = addr.get_struct();
        Descriptor tmp = ::socket(AF_INET, SOCK_STREAM, 0);
        socklen_t sock_size = sizeof(copy);
        int ret_val = ::connect(tmp.get_fd(), 
                                reinterpret_cast<sockaddr*> (&copy), 
                                sock_size);

        if (ret_val != 0)
            throw ConnectionFailed(addr.to_string());

        _sock = std::move(tmp);
    }
    void Connection::close() {
        if (!is_open()) 
            throw BadDescriptorUsed();
        
        _sock.close();
    }

    size_t Connection::read(char *buffer, size_t buf_len) {
        if (!is_open()) 
            throw BadDescriptorUsed();

        ssize_t ret_val = ::read(_sock.get_fd(), buffer, buf_len);

        if (ret_val == 0)
            throw SocketClosedRead();
        else if (ret_val == -1)
            throw ReadFailed();
        else 
            std::cerr << "Quantity of read bytes: " << ret_val << std::endl;

        return ret_val;
    }
    size_t Connection::write(const char *data, size_t buf_len) {
        if (!is_open()) 
            throw BadDescriptorUsed();

        ssize_t ret_val = ::write(_sock.get_fd(), data, buf_len);

        if (ret_val == -1)
            throw WriteFailed{};

        return ret_val;
    }
    
    void Connection::readExact(char *buffer, size_t buf_len) {
        size_t offset = 0;
        int count = 0;
        while (offset < buf_len) {
            size_t bytes_read = read(buffer + offset, buf_len);
            offset += bytes_read;
        }
    }
    void Connection::writeExact(const char *data, size_t buf_len) {
        size_t offset = 0;
        while (offset < buf_len) {
            size_t bytes_written = write(data + offset, buf_len);
            std::cerr << "Data: " << std::string_view{data, bytes_written};
            std::cerr << "Bytes written: " << bytes_written << std::endl;
            offset += bytes_written;
        }
    }

    void Connection::set_timeout(size_t ms) {
        timeval timeout{.tv_sec = 0, .tv_usec = 1000 * ms};
        if (setsockopt(_sock.get_fd(),
                        SOL_SOCKET,
                        SO_SNDTIMEO,
                        &timeout,
                        sizeof(timeout)) < 0)
            throw ClientTimeOutNotSetWrite();
        if (setsockopt(_sock.get_fd(),
                        SOL_SOCKET,
                        SO_RCVTIMEO,
                        &timeout,
                        sizeof(timeout)) < 0)
            throw ClientTimeOutNotSetRead{};
    }
    bool Connection::is_open() const noexcept {
        return (static_cast<bool>(_sock));
    }
} // namespace tcp