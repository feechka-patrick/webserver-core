#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	struct sockaddr_in peer;
	int s;
	int rc;
	char buf[1];
	// Заполняем поля структуры для использование ее в
	// connect
	peer.sin_family = AF_INET;
	peer.sin_port = htons(7500);                   //порт
	peer.sin_addr.s_addr = inet_addr("127.0.0.0"); //адрес означает, что сервер на той же машине, что и клиент

	//Создаем сокет
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == -1)
	{
		perror("socket call failed");
		exit(1);
	}
	// Устанавливаем соединение с сервером
	rc = connect(s, (struct sockaddr *)&peer,
				 sizeof(peer));
	if (rc == -1)
	{
		perror("connect call failed");
		exit(1);
	}
	//Посылаем серверу сообщение
	printf("Message for server: ");
	char message[1]; message[0] = getchar();
	rc = send(s, (void*)message, 1, 0);
	if (rc <= 0)
	{
		perror("send call failed");
		exit(1);
	}
	//получаем ответ
	rc = recv(s, buf, 1, 0);
	if (rc <= 0)
		perror("recv call failed");
	else
		printf("Server answer: %c\n", buf[0]);
	exit(0);
	return 0;
}