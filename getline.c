#include "shell.h"

/**
 * get_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @l: address of  var
 *
 * Return: bytes read
 */
ssize_t get_buf(info_t *info, char **buf, size_t *l)
{
	ssize_t r = 0;
	size_t k = 0;

	if (!*l)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &k, stdin);
#else
		r = _getline(info, buf, &k);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; 
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			
			{
				*l = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_lin - gets a line 
 * @info: parameter
 * Return: bytes read
 */
ssize_t get_lin(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) 
		return (-1);
	if (len) 
	{
		j = i;
		p = buf + i;

		check_chain(info, buf, &j, i, len);
		while (j < len) 
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; 
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf; 
	return (r); 
}

/**
 * read_buff - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buff(info_t *info, char *buf, size_t *k)
{
	ssize_t r = 0;

	if (*k)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*k = r;
	return (r);
}

/**
 * _getline - gets the next line of input.
 * @info: parameter struct
 * @ptr: address of pointer to buffer, 
 * @len: size of ptr buffer if not NULL
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *len)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, l;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && len)
		s = *len;
	if (i == l)
		i = l = 0;

	r = read_buf(info, buf, &l);
	if (r == -1 || (r == 0 && l == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : l;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (len)
		*len = s;
	*ptr = p;
	return (s);
}

/**
 * sig_handler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sig_handler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

