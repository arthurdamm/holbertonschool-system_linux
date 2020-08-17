#ifndef HHTTP_H
#define HHTTP_H

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

#define RESPONSE_200 "HTTP/1.1 200 OK\r\n\r\n"
#define RESPONSE_201 "HTTP/1.1 201 Created"
#define RESPONSE_404 "HTTP/1.1 404 Not Found\r\n\r\n"
#define RESPONSE_411 "HTTP/1.1 411 Length Required\r\n\r\n"
#define RESPONSE_422 "HTTP/1.1 422 Unprocessable Entity\r\n\r\n"

#define CONTENT_TYPE "Content-Type"
#define CONTENT_LENGTH "Content-Length"
#define URL_ENCODED "application/x-www-form-urlencoded"
#define JSON_TYPE "application/json"

#define PATH_TODOS "/todos"
#define METHOD_POST "POST"

#define KEY_TITLE "title"
#define KEY_DESCRIPTION "description"

/* server.c */
int accept_messages(int sd);
int send_response(int client_sd, char *response);
int parse_request(int client_sd, char *buf);

/* util.c */
char *trim(char *str);


#endif
