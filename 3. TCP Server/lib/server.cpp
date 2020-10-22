#include "server.hpp"
#include <iostream>

namespace tcp {
    Server::Server(std::string address, unsigned port, unsigned max_connection):
        _addr(address, port), _max_con(max_connection), _is_open(false), _is_set(true) {
        int fd = ::socket(AF_INET, SOCK_STREAM, 0);
        if(fd < 0) 
            std::cerr << "Error while creating socket" << std::endl;

        _d.set_fd(fd);
    }
    Server::Server(): _is_set(false), _is_open(false) {}
    Server::Server(Server &&other) {
        *this = std::move(other);
    }

    Server& Server::operator= (Server &&other) {
        _d = std::move(other._d);
        _timeout = other._timeout;
        _addr = other._addr;
        _max_con = other._max_con;

        _is_set = other._is_set;
        other._is_set = false;
        _is_open = other._is_open;
        other._is_open = false;

        return *this;
    }

    void Server::open(std::string address, unsigned port, unsigned max_connection) {
        struct sockaddr_in *copy = std::static_cast <struct sockaddr_in> 
            (new char [sizeof(struct sockaddr_in)]);
        *copy = _addr;
        socklen_t sock_size = sizeof(*copy);
        if (::bind(_d.get_fd(), 
                    reinterpret_cast<sockaddr*> (copy), 
                    sock_size) < 0)
            std::cerr << "Couldn't bind to the port" << std::endl;
        else {
            _is_open = true;
            _addr = *copy;
        }
    }
    Connection Server::accept() {
        if(::listen(_d.get_fd(), 1) < 0) 
            std::cerr << "Error while listening" << std::endl;
        else {
            struct sockaddr_in *copy = new struct sockaddr_in;
            socklen_t client_size = sizeof(*copy);
            int client_sock = ::accept(_d.get_fd(), 
                                    reinterpret_cast<sockaddr*> (copy), 
                                    &client_size);
            
            Address new_client = *copy;

            if (client_sock < 0)
                std::cout << "Can't accept" << std::endl;

            Descriptor new_d(client_sock);
            
            _clients.insert({new_client, std::move(new_d)});
            
            std::cerr << "Client connected at: " << new_client.to_string() << std::endl;

            return Connection(new_client, std::move(new_d));
        }
    }
    void Server::close() {
        if (_is_set)
            _d.close();

        for (auto&& [addr, desc] : _clients) {
            desc.close();
        }
    }

    void Server::set_max_connection(unsigned max_connection=SOMAXCONN) noexcept {
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