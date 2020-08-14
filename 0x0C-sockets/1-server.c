#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define PORT 12345

/**
 * main - socket server
 * @ac: argument vector
 * @av: argument count
 * Return: SUCCESS or FAILURE
 */
int main(int ac, char **av)
{
	struct sockaddr_in server, client;
	int sd, client_sd;
	socklen_t client_size = sizeof(client);
	char buf[INET_ADDRSTRLEN];

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
	client_sd = accept(sd, (struct sockaddr *)&client, &client_size);
	inet_ntop(AF_INET, &client.sin_addr, buf, sizeof(buf));
	printf("Client connected: %s\n", buf);
	close(client_sd);
	close(sd);
	return (EXIT_SUCCESS);
	(void)ac;
	(void)av;
}
