#ifndef SERVER_HPP
# define SERVER_HPP

# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <iostream>

class Server
{
	private:

		Server(const Server &obj);
		Server& operator= (const Server& obj);
	public:
		int fd;
		struct sockaddr_in address;

		Server();

		~Server();
};

#endif