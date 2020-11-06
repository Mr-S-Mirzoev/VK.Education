#include "server.hpp"
#include "exceptions.hpp"
#include <iostream>

/* Maximum queue length specifiable by listen.  */
#define SOMAXCONN	4096

namespace tcp {
    Server::Server(int port, unsigned max_con): _listen_socket(),
                                                _max_con(max_con), 
                                                _port(port) {
        bind();
        listen();
    }
    Server::Server(Server &&other): _listen_socket(std::move(other._listen_socket)),
                                    _port(other._port),
                                    _max_con(other._max_con) {}

    Server& Server::operator= (Server &&other) {
        _listen_socket = std::move(other._listen_socket);
        _max_con = other._max_con;
        _port = other._port;
        return *this;
    }

    void Server::listen () {
        if (::listen(_listen_socket.get_fd(), _max_con) < 0) {
            throw ServerListenError();
        }
    }

    void Server::bind() {
        /* 
        Bind a name to a given socket at _port
        */
        Address addr = server_address(_port);
        auto *addr_struct = new ::sockaddr_in{addr.get_struct()};
        int ret = ::bind(_listen_socket.get_fd(), 
                    reinterpret_cast<sockaddr*> (addr_struct), 
                    sizeof(*addr_struct));
        if (ret < 0)
            throw ServerBindError(_port);
    }

    Connection Server::accept() {
        try {
            ::sockaddr_in copy {0};
            socklen_t client_size = sizeof(copy);
            std::cerr << "Started accepting: " << _listen_socket.get_fd() << std::endl;
            int client_sock = ::accept(_listen_socket.get_fd(), 
                                        (struct sockaddr*) (&copy), 
                                        &client_size);
            std::cerr << "Ended" << std::endl;
            Address new_client = &copy;

            if (client_sock < 0)
                std::cout << "Can't accept" << std::endl;

            Descriptor new_d(client_sock);

            std::cerr << "Client connected at: " << new_client.to_string() << std::endl;
            return Connection(new_client, std::move(new_d));
        } catch (...) {
            throw ServerAcceptError();
        }
    }

    void Server::close() {
        if (_listen_socket)
            _listen_socket.close();
    }

    void Server::set_max_connection(unsigned max_connection) noexcept {
        _max_con = max_connection;
        listen();
    }

    void Server::set_timeout(size_t ms) {
        timeval timeout{.tv_sec = ms, .tv_usec = 0};
        if (::setsockopt(_listen_socket.get_fd(),
                        SOL_SOCKET,
                        SO_SNDTIMEO,
                        &timeout,
                        sizeof(timeout)) < 0)
        {
            std::cerr << "Set timeout error" << std::endl;
        }
    }
};