#ifndef HTTP_H
#define HTTP_H

#include <arpa/inet.h>
#include <ctype.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080
#define BUF_SIZE 8192
#define CRLF "\r\n"
#define SP " \t"
#define BACKLOG 8

#define RESPONSE_200_NOCRLF "HTTP/1.1 200 OK"
#define RESPONSE_200 (RESPONSE_200_NOCRLF CRLF CRLF)
#define RESPONSE_201 "HTTP/1.1 201 Created"
#define RESPONSE_204 "HTTP/1.1 204 No Content\r\n\r\n"
#define RESPONSE_404 "HTTP/1.1 404 Not Found\r\n\r\n"
#define RESPONSE_411 "HTTP/1.1 411 Length Required\r\n\r\n"
#define RESPONSE_422 "HTTP/1.1 422 Unprocessable Entity\r\n\r\n"

#define CONTENT_TYPE "Content-Type"
#define CONTENT_LENGTH "Content-Length"
#define URL_ENCODED "application/x-www-form-urlencoded"
#define JSON_TYPE "application/json"

#define PATH_TODOS "/todos"
#define METHOD_GET "GET"
#define METHOD_POST "POST"
#define METHOD_DELETE "DELETE"

#define KEY_ID "id"
#define KEY_TITLE "title"
#define KEY_DESCRIPTION "description"

/**
 * struct Todo - todo linked list structure
 * @id: id of current todo item
 * @title: title of current todo item
 * @description: description of current todo item
 * @next: next todo item in the linked lists
 */
typedef struct Todo
{
	int id;
	char *title;
	char *description;
	struct Todo *next;
} todo_t;

/* server.c */
int start_server(void);
int accept_messages(int sd);
int send_response(int client_sd, char *response);
int parse_request(int client_sd, char *buf);

/* util.c */
char *trim(char *str);


#endif
