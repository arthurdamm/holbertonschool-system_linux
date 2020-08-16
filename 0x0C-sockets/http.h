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

#define CONTENT_TYPE "Content-Type"
#define URL_ENCODED "application/x-www-form-urlencoded"

/* util.c */
char *trim(char *str);

#endif
