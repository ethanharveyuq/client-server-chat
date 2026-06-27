#include <cerrno>
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <thread>
#include <unistd.h>
#include <cstring>
#include "../include/server.hpp"


Server::Server(int lim, int port) {
    limit = lim;
    running = false;
    client_fds = {};
    // socket and bind
    open_server(port);
}

int Server::open_server(int port) {
    // initialise socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0); // TCP and IPv4
    if (server_fd < 0) {
        // handle error
        std::cerr << "Socket creation failed\n";
        return -1;
    }

    server_addr = sockaddr_in{};

    server_addr.sin_family = AF_INET; // IPv4
    server_addr.sin_port = htons(port);   // port chosen (default 0)
    server_addr.sin_addr.s_addr = INADDR_ANY;  // Bind to all available network interfaces

    if (bind(server_fd, (struct sockaddr*) &server_addr, sizeof(struct sockaddr)) < 0) {
        // socket bind failed, reason in errno
        std::cerr << "Socket bind failed\n";
        int serrno = errno; // save errno for caller
        close(server_fd);
        errno = serrno;
        return -1;     
    }

    return 0;
}

// Delete server functionality
Server::~Server() {
    if (server_fd >= 0) {
        close(server_fd);
    }
    // will clear the client_fds and mutex automatically (won't use new)
}

void Server::listen_accept() {
    running = true;
    int status = listen(server_fd, limit);
    if (status < 0) {
        std::cerr << "Server listening failed\n";
        return;
    }

    while (running) {
        int client_fd = accept(server_fd, nullptr, nullptr);

        if (client_fd < 0) {
            std::cerr << "Client accept failed\n";
            return;
        }
        client_fds.push_back(client_fd);

        std::thread(&Server::handle_client, this, client_fd).detach(); // detach for now, will use ctrl+C to end
    }
}

void Server::broadcast(const std::string& msg) {

}
void Server::handle_client(int fd) {

}