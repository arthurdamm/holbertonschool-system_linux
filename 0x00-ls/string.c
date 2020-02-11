#include "string.h"

/**
 * _strlen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *s)
{
	int i = 0;

	while (*s++)
		i++;
	return (i);
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

/**
 * UPPC - returns upper case char
 * @c: input char
 * Return: always uppercase
 */
char UPPC(char c)
{
	if (c >= 'A' && c <= 'Z')
		c += 'a' - 'A';
	return (c);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strings.
 * @s1: the first string
 * @s2: the second string
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	char *_s1 = s1, *_s2 = s2;

	while (*s1 && *s2)
	{
		if (*s1 == '.')
		{
			s1++;
			continue;
		}
		if (*s2 == '.')
		{
			s2++;
			continue;
		}
		if (UPPC(*s1) != UPPC(*s2))
			return (UPPC(*s1) - UPPC(*s2));
		s1++;
		s2++;
	}
	if (UPPC(*s1) == UPPC(*s2))
		return (_strcmpcase(_s1, _s2));
	else
		return (UPPC(*s1) < UPPC(*s2) ? -1 : 1);
}
