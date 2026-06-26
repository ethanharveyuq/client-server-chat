#include <vector>
#include <cerrno>
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

class Server {
    int listen_fd;
    std::vector<int> client_fds;
    std::mutex clients_mutex;
    struct sockaddr_in server_addr;
public:
    Server(int port = 0);
    ~Server();
    void broadcast(const std::string& msg);
    void handle_client(int fd);
};