#include <vector>
#include <cerrno>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

class Server {
    int server_fd;
    int limit;
    bool running;
    std::vector<int> client_fds;
    std::mutex clients_mutex;
    struct sockaddr_in server_addr;
    int open_server(int port);
public:
    Server(int lim, int port = 0);
    ~Server();
    void listen_accept();
    void broadcast(const std::string& msg);
    void handle_client(int fd);
};