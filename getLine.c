#include "simple_shell.h"
/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t n = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		n = getline(buf, &len_p, stdin);
#else
		n = _getline(info, buf, &len_p);
#endif
		if (n > 0)
		{
			if ((*buf)[n - 1] == '\n')
			{
				(*buf)[n - 1] = '\0';
				n--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			
			{
				*len = n;
				info->cmd_buf = buf;
			}
		}
	}
	return (n);
}
/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t k, m, leng;
	ssize_t n = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	n = input_buf(info, &buf, &leng);
	if (n == -1) 
		return (-1);
	if (leng)
	{
		m = k;
		p = buf + k;

		check_chain(info, buf, &m, k, leng);
		while (j < leng)
		{
			if (is_chain(info, buf, &m))
				break;
			m++;
		}

		k = m + 1; 
		if (k >= leng) 
		{
			k = leng = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf; 
	return (n); 
}
/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: n
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t n = 0;

	if (*i)
		return (0);
	n = read(info->readfd, buf, READ_BUF_SIZE);
	if (n >= 0)
		*i = n;
	return (n);
}
/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t k, leng;
	size_t i;
	ssize_t n = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (k == len)
		k = leng = 0;

	n = read_buf(info, buf, &leng);
	if (n == -1 || (n == 0 && leng == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	i = c ? 1 + (unsigned int)(c - buf) : leng;
	new_p = _realloc(p, s, s ? s + i : i + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + k, i - i);
	else
		_strncpy(new_p, buf + k, i - k + 1);

	s += i - k;
	k = i;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}
/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

