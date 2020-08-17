#include "http.h"

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
	if (listen(sd, BACKLOG) < 0)
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
		parse_request(client_sd, buf);
		send(client_sd, str, strlen(str), 0);
	}

	close(client_sd);
	return (EXIT_SUCCESS);
}

/**
 * parse_request - parses HTTP request
 * @client_sd: the client socket descriptor
 * @buf: string buffer containing message text
 * Return: 0 on success else 1
 */
int parse_request(int client_sd, char *buf)
{
	char *start_line, *path, *header, *body, *query, *key, *value, *save_ptr1,
		*save_ptr2;
	short url_encoded = 0;

	body = strstr(buf, CRLF CRLF);
	if (strlen(body))
	{
		*body = 0;
		body += strlen(CRLF CRLF);
	}
	start_line = strtok_r(buf, CRLF, &save_ptr1);
	strtok(start_line, SP);
	path = strtok(NULL, SP);
	path = strtok(path, "?");
	printf("Path: %s\n", path);
	header = strtok_r(NULL, CRLF, &save_ptr1);
	while (header)
	{
		key = trim(strtok_r(header, ":", &save_ptr2));
		value = trim(strtok_r(NULL, CRLF, &save_ptr2));
		if (!strcasecmp(key, CONTENT_TYPE))
		{
			if (!strcasecmp(value, URL_ENCODED))
				url_encoded = 1;
		}
		header = strtok_r(NULL, CRLF, &save_ptr1);
	}
	if (url_encoded)
	{
		query = strtok_r(body, "&", &save_ptr1);
		while (query)
		{
			key = strtok_r(query, "=", &save_ptr2);
			value = strtok_r(NULL, "=", &save_ptr2);
			printf("Body param: \"%s\" -> \"%s\"\n", key, value);
			query = strtok_r(NULL, "&", &save_ptr1);
		}
	}
	return (0);
	(void)client_sd;
}
