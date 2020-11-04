#include "server.hpp"
#include "exceptions.hpp"
#include <iostream>

/* Maximum queue length specifiable by listen.  */
#define SOMAXCONN	4096

namespace tcp {
    Server::Server(std::string address, unsigned port, unsigned max_con):
        _addr(address, port), _max_con(max_con) {
        int fd = ::socket(AF_INET, SOCK_STREAM, 0);
        if(fd < 0) 
            std::cerr << "Error while creating socket" << std::endl;

        _d.set_fd(fd);
    }
    Server::Server(Server &&other) {
        *this = std::move(other);
    }

    Server& Server::operator= (Server &&other) {
        _d = std::move(other._d);
        _addr = other._addr;
        _max_con = other._max_con;

        return *this;
    }





    void Server::open() {
        if (!is_open())
            throw BadDescriptorUsed();

        struct sockaddr_in *copy = static_cast <struct sockaddr_in *> 
            (new struct sockaddr_in);
        *copy = _addr.get_struct();
        socklen_t sock_size = sizeof(*copy);
        if (::bind(_d.get_fd(), 
                    reinterpret_cast<sockaddr*> (copy), 
                    sock_size) < 0)
            std::cerr << "Couldn't bind to the port" << std::endl;
        else {
            _addr = copy;
        }
    }
    Connection Server::accept() {
        listen(_max_con);
        struct sockaddr_in *copy = new struct sockaddr_in;
        socklen_t client_size = sizeof(*copy);
        int client_sock = ::accept(_d.get_fd(), 
                                reinterpret_cast<sockaddr*> (copy), 
                                &client_size);
        
        Address new_client = copy;

        if (client_sock < 0)
            std::cout << "Can't accept" << std::endl;

        Descriptor new_d(client_sock);

        std::cerr << "Client connected at: " << new_client.to_string() << std::endl;

        return Connection(new_client, std::move(new_d));
    }


    bool Server::is_open() const noexcept {
        return (!_d.broken());
    }
    void Server::close() {
        if (is_open())
            _d.close();
    }


    void Server::listen(const int queue_size) {
        if (is_open()) {
            if (::listen(_d.get_fd(), queue_size) < 0) {
                throw SocketClosed();
            }
        }
    }

    void Server::set_max_connection(unsigned max_connection) noexcept {
        listen(max_connection);
        _max_con = max_connection;
    }
    void Server::set_timeout(size_t ms) {
        timeval timeout{.tv_sec = ms, .tv_usec = 0};
        if (::setsockopt(_d.get_fd(),
                        SOL_SOCKET,
                        SO_SNDTIMEO,
                        &timeout,
                        sizeof(timeout)) < 0)
        {
            std::cerr << "Set timeout error" << std::endl;
        }
    }
};