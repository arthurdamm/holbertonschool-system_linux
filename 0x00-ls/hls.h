#ifndef HLS_HEADER
#define HLS_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>

#define MYNAME "hs"
#define BUF_SIZE 1024
#define STARTING_FILES_SIZE 1

/**
 * struct File - file info object
 * @name: base name of this file
 * @stat: the buf populated by lstat()
 */
typedef struct File
{
	char *name;
	struct stat stat;
} File;

#define FILE_INIT {NULL, NULL}

/**
 * struct Param - parameter pattern designed to deal with unclear requirements
 * and primitive obsession
 * @files: the array of files to process
 * @files_size: the currently allocated size of files
 * @files_i: the next availble index in files array
 */
typedef struct Param
{
	File *files;
	size_t files_size;
	size_t files_i;
} Param;

#define PARAM_INIT {NULL, 0, 0}

#include "string.h"
#include "lists.h"

/* hls.c */
void ls(char *path);
void parse_file(Param *param, char *name);
int checkdir(char *path);

/* error.c */
void error_cant_open(Param *param, char *name);
void error(int code);

/* alloc.c */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

#endif
