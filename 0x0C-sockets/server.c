#include "http.h"

/**
 * start_server - opens & binds inet socket and accepts messages
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int start_server(void)
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
	}

	close(client_sd);
	return (EXIT_SUCCESS);
}

/**
 * send_response - sends response back to client
 * @client_sd: client socket descriptor
 * @response: the response message
 * Return: 0 on success else 1
 */
int send_response(int client_sd, char *response)
{
	send(client_sd, response, strlen(response), 0);
	return (0);
}
