#include "http.h"

/**
 * main - socket server
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
	send_response(client_sd, RESPONSE_200);
	return (0);
}
