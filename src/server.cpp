#include <cerrno>
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include "../include/server.hpp"


Server::Server(int port) {
        // initialise socket
    listen_fd = socket(AF_INET, SOCK_STREAM, 0); // TCP and IPv4
    if (listen_fd < 0) {
        // handle error
        std::cerr << "Socket creation failed\n";
        return;
    }

    server_addr = sockaddr_in{};

    server_addr.sin_family = AF_INET; // IPv4
    server_addr.sin_port = htons(port);   // port chosen (default 0)
    server_addr.sin_addr.s_addr = INADDR_ANY;  // Bind to all available network interfaces

    if (bind(listen_fd, (struct sockaddr*) &server_addr, sizeof(struct sockaddr)) < 0) {
        // socket bind failed, reason in errno
        std::cerr << "Socket bind failed\n";
        int serrno = errno; // save errno for caller
        close(listen_fd);
        errno = serrno;
        return;     
    }
}

// Delete server functionality
Server::~Server() {
    if (listen_fd >= 0) {
        close(listen_fd);
    }
    // will clear the client_fds and mutex automatically (won't use new)
}

void Server::broadcast(const std::string& msg) {

}
void Server::handle_client(int fd) {

}