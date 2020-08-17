#include "http.h"

int accept_messages(int sd);
void parse_header(char *buf);

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
	return (send_response(client_sd, RESPONSE_200));
}
