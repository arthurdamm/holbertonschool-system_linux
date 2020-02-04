#ifndef STRING_H
#define STRING_H

#include "hls.h"

/* string.c */
int _strlen(char *s);
char *_strdup(const char *str);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);

/* string2.c */
char *starts_with(const char *haystack, const char *needle);

#endif
