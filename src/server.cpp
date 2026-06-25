#include <cerrno>
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

int create_server() {
    // initialise socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0); // TCP and IPv4
    if (socketfd < 0) {
        // handle error
        std::cerr << "Socket creation failed\n";
        return -1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr)); // clear

    server_addr.sin_family = AF_INET; // IPv4
    server_addr.sin_port = htons(0);   // no port chosen
    server_addr.sin_addr.s_addr = INADDR_ANY;  // Bind to all available network interfaces

    if (bind(socketfd, (struct sockaddr*) &server_addr, sizeof(struct sockaddr)) < 0) {
        // socket bind failed, reason in errno
        std::cerr << "Socket bind failed\n";
        int serrno = errno; // save errno for caller
        close(socketfd);
        errno = serrno;
        return -1;     
    }

    close(socketfd);
    return 0;
}