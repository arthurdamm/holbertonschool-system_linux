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
	char *start_line, *header, *key, *value, *save_ptr1, *save_ptr2;

	start_line = strtok_r(buf, CRLF, &save_ptr1);
	header = strtok_r(NULL, CRLF, &save_ptr1);
	while (header)
	{
		key = trim(strtok_r(header, ":", &save_ptr2));
		value = trim(strtok_r(NULL, CRLF, &save_ptr2));
		printf("Header: \"%s\" -> \"%s\"\n", key, value);
		header = strtok_r(NULL, CRLF, &save_ptr1);
	}
	send_response(client_sd, RESPONSE_200);
	return (0);
	(void)start_line;
}
