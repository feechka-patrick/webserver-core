#include "Client.hpp"

Client::Client(int server_fd)
{
    struct sockaddr_storage ss;
    socklen_t slen = sizeof(ss);

    int client_socket = accept(server_fd, (struct sockaddr *)&ss,
                               &slen);
    if (client_socket < 0)
    {
        perror("accept call failed");
        exit(EXIT_FAILURE);
    }
    // делаем fd неблокируемым
    fcntl(socket, F_SETFL, O_NONBLOCK);
}

Client::Client(int server_fd, struct sockaddr_in address)
{
    socklen_t slen = sizeof(address);
    
    socket = accept(server_fd, (struct sockaddr *)&address,
                               &slen);
    if (socket < 0)
    {
        perror("accept call failed");
        exit(EXIT_FAILURE);
    }
    //if (socket > FD_SETSIZE)
        // error

    // делаем fd неблокируемым
    fcntl(socket, F_SETFL, O_NONBLOCK);
}

Client::~Client() {
    close(socket);
}

Client::Client(const Client &obj) {
    this->socket = obj.socket;
    this->isResponseWaiting = obj.isResponseWaiting;
}

Client &Client::operator=(const Client &obj) {
    this->socket = obj.socket;
    this->isResponseWaiting = obj.isResponseWaiting;
    return *this;
}