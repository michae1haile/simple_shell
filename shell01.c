#include "shell.c"
/**
 *
 *
 */

int main (int argc, char *argv[], char *envp[])
{
	char **string;
	size_t n = 20, imbt = 0, pt = 4;
	size_t num_char;
	char *ptr, *nc;

	if (argc > 1)
		argv[1] = NULL;
	while (1)
	{
		if (isatty(STDIN_FILENO))

		printf("#cisfun$");

		ptr = malloc(sizeof(char) * n);
		num_char = getline(&ptr, &n, stdin);
		if (num_char == -1)
		{
			free(ptr);
			exit(EXIT_FAILURE);
		}
		if (*ptr != '\n')
		{
			string = chstrtok(ptr);
			if (_strcmp("exist", string[0] == 0)
					break;
					imbt = checkinbuilt(string[0]);
					nc = filechk(string[0]);
					if (imbt == 0 && nc != NULL)
					string[0] = nc;
					pt = pathchk(string[0]);
					if (pt == 1)
					forkexe(string, envp);
					if (nc == NULL && pt == 0 && imbt == 0)
					printf("./shell:no such file or directory\n");
		 }
	   }
	   free(nc);
	   free(ptr);
	   free(string);
	   exit(0);
}

/***
 *
 *
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
/**
 * chstrtok - print "$" first line
 * @str: string
 */
char **chstrtok(char *str)
{
	char **arst, *pars;
	int i = 0, j = 0;
	arst = malloc(8 * sizeof(char *));
	if (arst == NULL)
	{
		perror("can't allocate space");
		exit(1);
	}
	pars = strtok(str, " ");
	while (pars != NULL)
	{
		while (pars[j])
		{
			if (pars[j] == '\n')
				pars[i] = '\n';
			j++;
		}
			arst[i] = pars;
			i++;
			j = 0;
			pars = strtok(NULL, " ");
	}
		arst[i] = NULL;
		return (arst);
}

/**
 *
 *
 *
*/

void forkexe(char **arstr, char *envp[])
{
	pid_t child_pid;
	int status;
	child_pid = fork();
	if (child_pid < 0)
	{
		perror("Error:Fork issue");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(arstr[0], arstr, envp) == -1)
			perror("./shell:No such file or directory\n");
	}
	else
	{
		wait(&status);
	}
}
/**
 * filechk - func to check if sys cmd exist if so avoid fork calling
 * @str: string to apply the check
 * Return: applied the req'd path or NULL if false
 */
char *filechk(char *str)
{
	DIR *dir = opendir("/bin/");
	char *temp * cats;
	struct dirent *entity;
	if (dir == NULL)
		return (NULL);
	entity = readdir(dir);
	while (entity != NULL)
	{
		temp = entity->d_name;
		if (_strcmp(temp, str) == 0)
		{
			cats = _strcat("/bin/", str);
			closedir(dir);
			return (cats);
		}
		entity = readdir(dir);
	}
	closedir(dir);
	return (NULL);
}
/**
 * pathchk - fun. to check if the string has the path "/bin/"
 * @str: string to carryout the check
 * Return: 0 if false & 1 if true
 */
int pathchk(char *str)
{
	char *cmp = "/bin/", *ptr, *j;
	int i = 0, p = 0;

	ptr = malloc(sizeof(char) * 50);
	if (ptr == NULL)
		return (0);
	while (cmp[i] != '\0')
	{
		if (cmp[i] != str[i])
		{
			free(ptr);
			return (0);
		}
	i++;
	}
	while (str[i] != '\0')
	{
		ptr[p] = str[i];
		p++;
		i++;
	}
	ptr[p] = '\0';
	j = filechk(ptr);
	if (j != NULL)
	{
		free(ptr);
		return (1);
	}
	return (0);
}

