#include <string>

void send_message(std::string& msg, int sock_fd);

void receive_message(int sock_fd);

void connect(int sock_fd);

void disconnect(int sock_fd);