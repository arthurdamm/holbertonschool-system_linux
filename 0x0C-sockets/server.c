#include "http.h"

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
	printf("RESPONSE: %s\n", response);
	send(client_sd, response, strlen(response), 0);
	return (0);
}
