#include "server.hpp"
#include "exceptions.hpp"
#include <iostream>

namespace tcp {

    Server::Server(const Address &addr, unsigned max_con): _listen_socket(create_inet4_socket()),
                                                _max_con(max_con), 
                                                _address(addr) {
        bind();
        listen();
    }
    Server::Server(Server &&other): _listen_socket(std::move(other._listen_socket)),
                                    _address(other._address),
                                    _max_con(other._max_con) {}

    Server& Server::operator= (Server &&other) {
        _listen_socket = std::move(other._listen_socket);
        _max_con = other._max_con;
        _address = other._address;
        return *this;
    }

    void Server::listen () {
        if (::listen(_listen_socket.get_fd(), _max_con) < 0)
            throw ServerListenError{};
    }

    void Server::bind() {
        /* 
        Bind a name to a given socket at _port
        */
        ::sockaddr_in remote = _address.get_struct();
        int ret = ::bind(_listen_socket.get_fd(), 
                    reinterpret_cast<sockaddr*> (&remote), 
                    sizeof(remote));
        if (ret < 0)
            throw ServerBindError{_port};
    }

    Connection Server::accept() {
        try {
            ::sockaddr_in copy {};
            socklen_t client_size = sizeof(copy);
            std::cerr << "Started accepting: " << std::endl;
            int client_sock = ::accept(_listen_socket.get_fd(), 
                                        (struct sockaddr*) (&copy), 
                                        &client_size);
            std::cerr << "Ended" << std::endl;
            Address new_client = copy;

            if (client_sock < 0)
                std::cout << "Can't accept" << std::endl;

            Descriptor new_d(client_sock);

            std::cerr << "Client connected at: " << new_client.to_string() << std::endl;
            return Connection(new_client, std::move(new_d));
        } catch (BadDescriptorUsed) {
            throw ServerAcceptError();
        }
    }

    void Server::close() {
        if (_listen_socket)
            _listen_socket.close();
    }

    void Server::set_max_connection(unsigned max_connection) noexcept {
        listen();
        _max_con = max_connection;
    }

    void Server::set_timeout(size_t ms) {
        timeval timeout{.tv_sec = 0, .tv_usec = 1000 * ms};
        if (::setsockopt(_listen_socket.get_fd(),
                        SOL_SOCKET,
                        SO_RCVTIMEO,
                        &timeout,
                        sizeof(timeout)) < 0)
            throw ServerTimeOutNotSet{};
    }
} // namespace tcp