# include "Server.hpp"

# define PORT 7500
# define IP_ADDR "127.0.0.0"
# define MAX_CLIENTS 5

Server::Server() {
	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);
	address.sin_addr.s_addr = inet_addr(IP_ADDR);

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0)
	{
		perror("sock call failed");
		exit(EXIT_FAILURE);
	}

	// SO_REUSEADDR для переиспользования сокета даже если он занят
	int opt = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
	{
		std::cerr << "setsockopt call failure" << std::endl;
		exit(EXIT_FAILURE);
	}

	if (bind(fd, (struct sockaddr *)&address,
			 sizeof(address)) < 0)
	{
		perror("bind call failure");
		exit(EXIT_FAILURE);
	}

	// backlog - maximum number of pending connections

	if (listen(fd, MAX_CLIENTS) < 0)
	{
		perror("listen call failed");
		exit(EXIT_FAILURE);
	}
}

Server::Server(const Server &obj) {
    this->fd = obj.fd;
    this->address = obj.address;
}

Server::~Server() {}

Server& Server::operator= (const Server& obj) {
    this->fd = obj.fd;
    this->address = obj.address;
    return *this;
}