#include "connection.hpp"
#include "exceptions.hpp"

#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <string_view>

namespace tcp {
    Connection::Connection(const Address &addr): _addr(addr), _sock(socket(AF_INET, SOCK_STREAM, 0)) {}
    Connection::Connection(const Address &addr, Descriptor &&d): _addr(addr), _sock(std::move(d)) {}
    Connection::Connection(Connection &&con): _addr(con._addr), _sock(std::move(con._sock)) {}

    Connection& Connection::operator=(Connection &&con) noexcept {
        _addr = con._addr;
        _sock = std::move(con._sock);
        return *this;
    }
  
    void Connection::connect(const Address &addr) {
        struct sockaddr_in copy = addr.get_struct();
        socklen_t sock_size = sizeof(copy);
        int ret_val = ::connect(_sock.get_fd(), 
                                reinterpret_cast<sockaddr*> (&copy), 
                                sock_size);

        if (ret_val != 0)
            throw ConnectionFailed(addr.to_string());
    }
    void Connection::close() {
        if (!is_open()) 
            throw BadDescriptorUsed();
        
        _sock.close();
    }

    size_t Connection::read(char *buffer, size_t buf_len) {
        if (!is_open()) 
            throw BadDescriptorUsed();

        size_t ret_val = ::read(_sock.get_fd(), buffer, buf_len);

        if (ret_val == 0)
            throw SocketClosedRead();
        else
            std::cerr << "Quantity of read bytes: " << ret_val << std::endl;

        return ret_val;
    }
    size_t Connection::write(const char *data, size_t buf_len) {
        if (!is_open()) 
            throw BadDescriptorUsed();

        size_t ret_val = ::write(_sock.get_fd(), data, buf_len);

        return ret_val;
    }
    
    void Connection::readExact(char *buffer, size_t buf_len) {
        size_t offset = 0;
        int count = 0;
        try {
            while (offset < buf_len) {
                try {
                    size_t bytes_read = read(buffer + offset, buf_len);

                    if (count > 0)
                        count = 0;
                    
                    offset += bytes_read;
                } catch (SocketClosedRead &e) {
                    std::cerr << e.what() << std::endl;
                    ++count;
                    if (count == 3)
                        throw ReadFailed{};
                }
            }
        } catch (BadDescriptorUsed &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    void Connection::writeExact(const char *data, size_t buf_len) {
        size_t offset = 0;
        try {
            while (offset < buf_len) {
                size_t bytes_written = write(data + offset, buf_len);
                std::cerr << "Data: " << std::string_view{data, bytes_written};
                std::cerr << "Bytes written: " << bytes_written << std::endl;
                offset += bytes_written;
            }
        } catch (SocketClosedWrite &e) {
            std::cerr << e.what() << std::endl;
        } catch (BadDescriptorUsed &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void Connection::set_timeout(size_t ms) {
        timeval timeout{.tv_sec = 0, .tv_usec = ms};
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
        return (bool(_sock));
    }

    Connection::~Connection() {
        ::shutdown(_sock, SHUT_RD);
        ::shutdown(_sock, SHUT_WR);
        ::shutdown(_sock, SHUT_RDWR);
    }
} // namespace tcp