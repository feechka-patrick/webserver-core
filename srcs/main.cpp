
#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include "Client.hpp"
#include "Server.hpp"

#define PORT 7500
#define IP_ADDR "127.0.0.0"
#define MAX_CLIENTS 5

std::string readFile(const std::string &fileName)
{
	std::ifstream f(fileName.c_str());
	std::stringstream ss;
	ss << f.rdbuf();
	return ss.str();
}

void getRequest(int client_socket)
{
	// получаем сообщение от клиента
	const int BUFSIZE = 100;
	char buf[BUFSIZE];
	if (recv(client_socket, buf, BUFSIZE, 0) <= 0)
	{
		perror("recv call failed");
		exit(EXIT_FAILURE);
	}
	printf("CLIENT MESSAGE: %s\n", buf);
}

void doResponse(int client_socket)
{
	// отправляем ответ
	std::string response = readFile("response-example/1");
	if (send(client_socket, (void *)response.c_str(), response.size(), 0) <= 0)
		perror("send call failed");
	printf("SERVER ANSWER: ");
	std::cout << response << std::endl;
	std::cin >> response;
	std::cout << "\n";
}

int main(void)
{
	Server server;

	//  MAIN PART START ----------------------------

	fd_set readset, writeset, exset;
	std::vector<Client *> clients;
	while (true)
	{
		FD_ZERO(&readset);
		FD_ZERO(&writeset);
		FD_ZERO(&exset);

		FD_SET(server.fd, &readset);

		int maxfd = server.fd;
		for (unsigned long i = 0; i < clients.size(); ++i)
		{
			FD_SET(clients[i]->socket, &readset);
			if (clients[i]->isResponseWaiting)
			{
				FD_SET(clients[i]->socket, &writeset);
			}
			if (clients[i]->socket > maxfd)
				maxfd = clients[i]->socket;
		}

		struct timeval timeout;
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;

		printf("\n+++++++ Waiting for new connection ++++++++\n\n");
		int select_res = select(maxfd + 1, &readset,
							NULL, NULL, &timeout);

		if (select_res < 0)
		{
			perror("select call failed");
			exit(EXIT_FAILURE);
		}
		if (select_res == 0) continue;


		// добавление нового соединения
		if (FD_ISSET(server.fd, &readset))
		{
			Client* new_client = new Client(server.fd, server.address);
			clients.push_back(new_client);
		}

		for (unsigned long i = 0; i < clients.size(); ++i)
		{
			if (FD_ISSET(clients[i]->socket, &readset))
			{
				getRequest(clients[i]->socket);
			}
			else if (FD_ISSET(clients[i]->socket, &writeset) && clients[i]->isResponseWaiting)
			{
				doResponse(clients[i]->socket);
			}
		}

		printf("------------------ Close connection -------------------\n");
	}

	//  MAIN PART END ------------------------------

	close(server.fd);
	return 0;
}