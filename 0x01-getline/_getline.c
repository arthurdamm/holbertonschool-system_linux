#include "_getline.h"

/**
 * __getline - gets a line of chars from a file descriptor
 * @fd: the file descriptor to read
 *
 * Return: pointer to the line
 */
char *__getline(const int fd)
{
	static FdBuf head;
	FdBuf *fb = NULL, *temp;
	char *line = NULL;

	if (fd == -1)
	{
		if (head.buf)
			head.buf = (free(head.buf), NULL);
		for (fb = head.next; fb;)
		{
			if (fb->buf)
			{
				free(fb->buf);
				fb->buf = NULL;
			}
			temp = fb;
			fb = fb->next;
			free(temp);
		}
		memset(&head, 0, sizeof(head));
		return (NULL);
	}
	fb = get_fdbuf(&head, fd);
	if (fb)
		line = read_buf(fb);
	if (line && line[0] == '\n' && !line[1])
		line[0] = 0;
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

	p = __strchr(fb->buf + fb->i, '\n', fb->len - fb->i);
	if (!fb->len || fb->i >= fb->len || !p)
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
			p = __strchr(fb->buf + (fb->len - r), '\n', r);
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

	if (!head->buf && !head->fd && !head->next)
	{
		head->fd = fd;
		return (head);
	}
	for (; head->next && head->next->fd <= fd; head = head->next)
		;
	if (head->fd == fd)
		return (head);
	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	if (fd < head->fd) /* need to copy head over and replace */
	{
		memcpy(node, head, sizeof(*head));
		memset(head, 0, sizeof(*head));
		head->fd = fd;
		head->next = node;
		return (head);
	}
	memset(node, 0, sizeof(*node));
	node->fd = fd;
	node->next = head->next;
	head->next = node;
	return (node);
}

/**
 **__strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *@size: number of bytes to search
 *Return: (s) a pointer to the memory area s
 */
char *__strchr(char *s, char c, ssize_t size)
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
