#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>

#define USAGE "Usage: %s <host> <port>\n"

/**
 * main - socket client
 * @ac: argument vector
 * @av: argument count
 * Return: SUCCESS or FAILURE
 */
int main(int ac, char **av)
{
	struct sockaddr_in server;
	int sd;
	struct hostent *host;

	if (ac != 3)
		return (printf(USAGE, av[0]), EXIT_FAILURE);

	host = gethostbyname(av[1]);
	sd = socket(PF_INET, SOCK_STREAM, 0);
	if (sd < 0)
	{
		perror("socket failed");
		return (EXIT_FAILURE);
	}
	server.sin_family = AF_INET;
	inet_pton(AF_INET, inet_ntoa(*(struct in_addr *)host->h_addr),
		&server.sin_addr);
	server.sin_port = htons(atoi(av[2]));
	if (connect(sd, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		perror("connect failure");
		return (EXIT_FAILURE);
	}

	printf("Connected to %s:%s\n", av[1], av[2]);
	close(sd);
	return (EXIT_SUCCESS);
	(void)ac;
	(void)av;
}
