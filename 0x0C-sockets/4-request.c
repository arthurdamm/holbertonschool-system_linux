#include "http.h"

/**
 * main - entry point
 * @ac: argument vector
 * @av: argument count
 * Return: SUCCESS or FAILURE
 */
int main(int ac, char **av)
{
	return (start_server());
	(void)ac;
	(void)av;
}

/**
 * parse_request - parses HTTP header and prints fields
 * @client_sd: the client socket descriptor
 * @buf: string buffer containing message text
 * Return: 0 on success else 1
 */
int parse_request(int client_sd, char *buf)
{
	char *DELIMS = " \t\r\n";
	char *method, *path, *version;

	method = strtok(buf, DELIMS);
	path = strtok(NULL, DELIMS);
	version = strtok(NULL, DELIMS);
	printf("Method: %s\nPath: %s\nVersion: %s\n", method, path, version);
	return (send_response(client_sd, RESPONSE_200));
}
