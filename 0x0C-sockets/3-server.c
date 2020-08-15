#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define PORT 12345
#define BUF_SIZE 8192

int accept_messages(int sd);

/**
 * main - socket server
 * @ac: argument vector
 * @av: argument count
 * Return: SUCCESS or FAILURE
 */
int main(int ac, char **av)
{
	struct sockaddr_in server;
	int sd;

	sd = socket(PF_INET, SOCK_STREAM, 0);
	if (sd < 0)
	{
		perror("socket failed");
		return (EXIT_FAILURE);
	}
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sd, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		perror("bind failure");
		return (EXIT_FAILURE);
	}
	if (listen(sd, 10) < 0)
	{
		perror("listen failure");
		return (EXIT_FAILURE);
	}
	printf("Server listening on port %d\n", ntohs(server.sin_port));
	accept_messages(sd);
	close(sd);
	return (EXIT_SUCCESS);
	(void)ac;
	(void)av;
}

/**
 * accept_messages - accepts messages from server socket
 * @sd: the server socket
 * Return: SUCCESS or FAILURE
 */
int accept_messages(int sd)
{
	int client_sd;
	struct sockaddr_in client;
	socklen_t client_size = sizeof(client);
	char buf[BUF_SIZE + 1];
	ssize_t bytes_read;


	client_sd = accept(sd, (struct sockaddr *)&client, &client_size);
	if (client_sd < 0)
	{
		perror("accept failure");
		return (EXIT_FAILURE);
	}
	inet_ntop(AF_INET, &client.sin_addr, buf, INET_ADDRSTRLEN);
	printf("Client connected: %s\n", buf);

	bytes_read = recv(client_sd, buf, BUF_SIZE, 0);
	if (bytes_read > 0)
	{
		buf[bytes_read] = 0;
		printf("Message received: \"%s\"\n", buf);
	}

	close(client_sd);
	return (EXIT_SUCCESS);
}
