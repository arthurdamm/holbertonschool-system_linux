#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>

#define PORT 12345

/**
 * main - socket server
 * @ac: argument vector
 * @av: argument count
 * Return: SUCCESS or FAILURE
 */
int main(int ac, char **av)
{
	int sd;
	struct sockaddr_in name;

	sd = socket(PF_INET, SOCK_STREAM, 0);
	if (sd < 0)
	{
		perror("socket failed");
		return (EXIT_FAILURE);
	}
	name.sin_family = AF_INET;
	name.sin_port = htons(PORT);
	name.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sd, (struct sockaddr *)&name, sizeof(name)) < 0)
	{
		perror("bind failure");
		return (EXIT_FAILURE);
	}
	if (listen(sd, 10) < 0)
	{
		perror("listen failure");
		return (EXIT_FAILURE);
	}

	printf("LISTENING...\n");
	while (1)
		;
	return (EXIT_SUCCESS);
	(void)ac;
	(void)av;
}
