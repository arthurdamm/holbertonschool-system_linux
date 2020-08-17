#include "http.h"

static int ids;
static todo_t *todo_root;

int post_request(int client_sd, char *body, short content_length);

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
 * parse_request - parses HTTP request
 * @client_sd: the client socket descriptor
 * @buf: string buffer containing message text
 * Return: 0 on success else 1
 */
int parse_request(int client_sd, char *buf)
{
	char *start_line, *method, *path, *header, *body, *key, *value,
		*save_ptr1, *save_ptr2;
	short url_encoded = 0, content_length = 0;

	body = strstr(buf, CRLF CRLF);
	if (strlen(body))
	{
		*body = 0;
		body += strlen(CRLF CRLF);
	}
	start_line = strtok_r(buf, CRLF, &save_ptr1);
	method = strtok(start_line, SP);
	path = strtok(NULL, SP);
	path = strtok(path, "?");
	if (strcasecmp(method, METHOD_POST) || strcasecmp(path, PATH_TODOS))
		return (send_response(client_sd, RESPONSE_404));
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
		else if (!strcasecmp(key, CONTENT_LENGTH))
			content_length = atoi(value);
		header = strtok_r(NULL, CRLF, &save_ptr1);
	}

	if (!content_length)
		return (send_response(client_sd, RESPONSE_411));
	post_request(client_sd, body, content_length);
	return (0);
	(void)url_encoded;
}

/**
 * post_request - parses post request
 * @client_sd: the client socket descriptor
 * @body: the body string
 * @content_length: length of body string
 * Return: 0 on success else 1
 */
int post_request(int client_sd, char *body, short content_length)
{
	char *query, *key, *value, *save_ptr1, *save_ptr2,
		*title = NULL, *description = NULL;
	char buf1[1024] = {0}, buf2[1024] = {0};
	todo_t *todo, *node;

	body[content_length] = 0;
	query = strtok_r(body, "&", &save_ptr1);
	while (query)
	{
		key = strtok_r(query, "=", &save_ptr2);
		value = strtok_r(NULL, "=", &save_ptr2);
		printf("Body param: \"%s\" -> \"%s\"\n", key, value);
		if (!strcasecmp(key, KEY_TITLE))
			title = value;
		else if (!strcasecmp(key, KEY_DESCRIPTION))
			description = value;
		query = strtok_r(NULL, "&", &save_ptr1);
	}
	if (!title || !description)
		return (send_response(client_sd, RESPONSE_422));

	todo = calloc(1, sizeof(*todo));
	if (!todo)
		return (1);
	todo->id = ids++;
	todo->title = strdup(title);
	todo->description = strdup(description);
	if (!todo_root)
		todo_root = todo;
	else
	{
		node = todo_root;
		while (node->next)
			node = node->next;
		node->next = todo;
	}
	sprintf(buf2, "{\"" KEY_ID "\":%d,\"" KEY_TITLE "\":\"%s\",\""
		KEY_DESCRIPTION "\":\"%s\"}", ids - 1, title, description);
	sprintf(buf1, RESPONSE_201 CRLF CONTENT_LENGTH ": %lu" CRLF
		CONTENT_TYPE ": " JSON_TYPE CRLF CRLF "%s", strlen(buf2), buf2);
	send_response(client_sd, buf1);
	return (0);
}
