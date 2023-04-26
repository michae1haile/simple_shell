#include "shell.h"

/**
* main -  shell that reads user input from standard input using the read function and executes commands
* using the execve function.
* Return: 0 (success)
*/
int main(void)
{
	char *cmdline;

	pid_t pid;
	int status;

	*cmdline = malloc(MAX_CMD_LENGTH * sizeof(char)):

	while (1)
	{
		write(STDOUT_FILENO, ">> ", 3);

		ssize_t nread;

		nread = read(STDIN_FILENO, cmdline, MAX_CMD_LENGTH);
		if (nread == 0)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}
		else if (nread < 0)
		{
			perror("read");
			continue;
		}
		if (cmdline[nread - 1] == '\n')
		{
			cmdline[nread - 1] = '\0';
			nread--;
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			continue;
		}
		if (pid == 0)
		{
			if (execve(cmdline, NULL, NULL) < 0)
			{
				perror("execve");
				_exit(1);
			}
		}
		else
		{
			waitpid(pid, &status, 0);
		}
	}
	free(cmdline);
	return (0);
}
