#ifndef HLS_HEADER
#define HLS_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#define MYNAME "hls"
#define BUF_SIZE 1024
#define STARTING_FILES_SIZE 1

#define RUSR (file->stat.st_mode & S_IRUSR ? 'r' : '-')
#define WUSR (file->stat.st_mode & S_IWUSR ? 'w' : '-')
#define XUSR (file->stat.st_mode & S_IXUSR ? 'x' : '-')
#define RGRP (file->stat.st_mode & S_IRGRP ? 'r' : '-')
#define WGRP (file->stat.st_mode & S_IWGRP ? 'w' : '-')
#define XGRP (file->stat.st_mode & S_IXGRP ? 'x' : '-')
#define ROTH (file->stat.st_mode & S_IROTH ? 'r' : '-')
#define WOTH (file->stat.st_mode & S_IWOTH ? 'w' : '-')
#define XOTH (file->stat.st_mode & S_IXOTH ? 'x' : '-')

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
 * struct list_f - singly linked list
 * @file: the file struct value
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 * for Holberton project
 */
typedef struct list_f
{
	File file;
	struct list_f *next;
} list_t;

/**
 * struct Param - parameter pattern designed to deal with unclear requirements
 * and primitive obsession
 * @files: the array of files to process
 * @files_size: the currently allocated size of files
 * @files_i: the next availble index in files array
 * @sorted_files: pointers to Files in sorted order
 * @dirs: linked list queue of dirs
 * @status: the return code
 * @multiple_dirs: true if printing headers for > 1 dirs
 * @printed_dir: true if already printed a dir before
 * @options: the dash-separated command options
 * @nonoption_argument: true if there was nonoption arg
 */
typedef struct Param
{
	File *files;
	size_t files_size;
	size_t files_i;

	File **sorted_files;

	list_t *dirs;

	int status;
	int multiple_dirs;
	int printed_dir;
	int options;
	int nonoption_argument;

} Param;

#define PARAM_INIT {NULL, 0, 0, NULL, NULL, EXIT_SUCCESS, 0, 0, 0, 0}

#define OPTION_1 0x01
#define OPTION_a 0x02
#define OPTION_A 0x04
#define OPTION_l 0x08
#define OPTION_R 0x10

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define MAX(a, b) ((a) > (b) ? (a) : (b))

#include "string.h"
#include "lists.h"

/* hls.c */
int ls(Param *param, char *path);

/* files.c */
void append_file(Param *param, char *name);
void print_files(Param *param, int omit_dirs);
void filter_dirs_from_files(Param *param);
void print_dirs(Param *param);
void populate_sorted_files(Param *param);

/* error.c */
void error_cant_open(Param *param, char *name);
void error_bad_option(Param *param, char c);
void error(int code);

/* param.c */
void free_param(Param *param);
void free_names(Param *param);

/* utils.c */
int is_dir(File *file);
void parse_options(Param *param, char *arg);
char *base_name(char *fullpath);
char *sprint_time(File *file);
char *convert_number(long int num, int base, int flags);

/* utils2.c */
void print_file_long(Param *param, File *file, size_t *sizes);
void get_long_format_field_sizes(Param *param, size_t *sizes, int omit_dirs);

/* alloc.c */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void *_memset(void *p, char b, unsigned int n);

/* sort.c */
void quick_sort(Param *param, File **array, size_t size);

#endif
