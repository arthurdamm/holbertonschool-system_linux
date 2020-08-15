#include "http.h"

int accept_messages(int sd);
void parse_header(char *buf);

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

	setbuf(stdout, NULL);
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
	if (listen(sd, 8) < 0)
	{
		perror("listen failure");
		return (EXIT_FAILURE);
	}
	printf("Server listening on port %d\n", ntohs(server.sin_port));
	while (1)
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
	char buf[BUF_SIZE + 1] = {0};
	ssize_t bytes_read;
	char *str = "HTTP/1.1 200 OK\r\n\r\n";


	client_sd = accept(sd, (struct sockaddr *)&client, &client_size);
	if (client_sd < 0)
	{
		perror("accept failure");
		return (EXIT_FAILURE);
	}
	inet_ntop(AF_INET, &client.sin_addr, buf, INET_ADDRSTRLEN);
	printf("Client connected: %s\n", buf);

	buf[0] = 0;
	bytes_read = recv(client_sd, buf, BUF_SIZE, 0);
	if (bytes_read > 0)
	{
		buf[bytes_read] = 0;
		printf("Raw request: \"%s\"\n", buf);
		parse_header(buf);
		send(client_sd, str, strlen(str), 0);
	}

	close(client_sd);
	return (EXIT_SUCCESS);
}

/**
 * parse_header - parsers HTTP header and prints fields
 * @buf: string buffer containing message text
 */
void parse_header(char *buf)
{
	char *DELIMS = " \t\r\n";
	char *path, *query, *save1, *key, *value, *save2;

	strtok(buf, DELIMS);
	path = strtok(NULL, DELIMS);
	path = strtok_r(path, "?", &save1);
	printf("Path: %s\n", path);
	query = strtok_r(NULL, "&", &save1);
	while (query)
	{
		key = strtok_r(query, "=", &save2);
		value = strtok_r(NULL, "=", &save2);
		printf("Query: \"%s\" -> \"%s\"\n", key, value);
		query = strtok_r(NULL, "&", &save1);
	}
}
