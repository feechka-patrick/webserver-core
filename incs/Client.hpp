#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>

# include <iostream>

class Client
{
	private:

		Client();
		Client(const Client &obj);
		Client& operator= (const Client& obj);
	public:
		int         socket;
        std::string buf;
        bool        isResponseWaiting;

		Client(int server_fd);

		Client(int server_fd, struct sockaddr_in address);
        
		~Client();
};

#endif