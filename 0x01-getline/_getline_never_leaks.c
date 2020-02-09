#include "_getline.h"

/**
 * _getline - gets a line of chars from a file descriptor
 * @fd: the file descriptor to read
 *
 * Return: pointer to the line
 */
char *_getline(const int fd)
{
	static FdBuf head;
	static char buf[READ_SIZE + 1];
	static size_t len;
	FdBuf *fb = NULL, *temp;
	char *line = NULL;

	if (fd == -1)
	{
		if (head.buf)
			head.buf = (free(head.buf), NULL);
		for (fb = head.next; fb;)
		{
			if (fb->buf)
				fb->buf = (free(fb->buf), NULL);
			temp = fb;
			fb = fb->next;
			free(temp);
		}
		memset(&head, 0, sizeof(head)), memset(buf, 0, len), len = 0;
		return (NULL);
	}
	fb = get_fdbuf(&head, fd);
	if ((fb == &head) && len)
	{
		fb->buf = malloc(len + 1);
		if (!fb->buf)
			return (NULL);
		memcpy(fb->buf, buf, fb->len = len);
		len = 0;
	}
	if (fb)
		line = read_buf(fb);
	if ((fb == &head) && fb->buf)
	{
		memcpy(buf, fb->buf + fb->i, len = fb->len - fb->i);
		fb->buf = (free(fb->buf), NULL);
		fb->len = fb->i = 0;
	}
	return (line);
}

/**
 * read_buf - reads into the buffer
 * @fb: the fd buf struct
 *
 * Return: 0 on success else -1 on error.
 */
char *read_buf(FdBuf *fb)
{
	char buf[READ_SIZE + 1], *p, *line;
	ssize_t r = 0;

	p = _strchr(fb->buf + fb->i, '\n', fb->len - fb->i);
	if (!fb->len || fb->i + 1 == fb->len || !p)
	{
		while (1)
		{
			r = read(fb->fd, buf, READ_SIZE);
			if (r < 0 || (r == 0 && !fb->len))
				return (fb->buf ? (free(fb->buf), NULL) : NULL);
			if (r == 0)
			{
				p = fb->buf + fb->len;
				break;
			}
			fb->buf = _realloc(fb->buf, fb->len, fb->len + r + 1);
			if (!fb->buf)
				return (NULL);
			memcpy(fb->buf + fb->len, buf, r), fb->len += r;
			p = _strchr(fb->buf + (fb->len - r), '\n', r);
			if (p)
			{
				fb->buf[fb->len] = 0;
				break;
			}
		}
	}
	*p = '\0';
	line = malloc(1 + (p - (fb->buf + fb->i)));
	if (!line)
		return (NULL);
	memcpy(line, fb->buf + fb->i, 1 + (p - (fb->buf + fb->i)));
	fb->i = (p - fb->buf) + 1;
	if (fb->i >= fb->len)
	{
		fb->i = fb->len = 0;
		fb->buf = (free(fb->buf), NULL);
	}
	return (line);
}

/**
 * get_fdbuf - adds a car to linked list
 * @head: pointer to head node
 * @fd: file descriptor of buffer to get
 * Return: pointer to the fd buf node
 */
FdBuf *get_fdbuf(FdBuf *head, const int fd)
{
	FdBuf *node;

	if (!head->fd && !head->next)
	{
		head->buf = NULL;
		head->fd = fd;
		return (head);
	}
	else if (fd < head->fd) /* need to copy head over and replace */
	{
		node = malloc(sizeof(*node));
		if (!node)
			return (NULL);
		memcpy(node, head, sizeof(*head));
		memset(head, 0, sizeof(*head));
		head->buf = NULL;
		head->fd = fd;
		head->next = node;
		return (head);
	}
	for (; head->next && head->next->fd <= fd; head = head->next)
		;
	if (head->fd == fd)
	{
		return (head);
	}
	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	memset(node, 0, sizeof(*node));
	node->buf = NULL;
	node->fd = fd;
	node->next = head->next;
	head->next = node;
	return (node);
}

/**
 **_strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *@size: number of bytes to search
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c, ssize_t size)
{
	if (!s)
		return (NULL);
	do {
		if (*s == c)
			return (s);
		s++;
	} while (--size > 0);
	return (NULL);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

