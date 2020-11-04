#include "server.hpp"
#include <iostream>

int main () {
    tcp::Server s("127.1.1.1", 8888);
    s.open();
    s.set_max_connection(5);
    std::cout << "accepting:\n";
    tcp::Connection connection = s.accept();
    std::cout << "Connection: " << std::boolalpha << connection.is_open() << std::endl;
    auto dest = connection.getDstAddr();
    auto[src_ip, src_port] = connection.getSrcAddr();
    std::cout << "Dst: " << dst_ip << ' ' << dst_port << std::endl;
    std::cout << "Src: " << src_ip << ' ' << src_port << std::endl;
    server.close();
}