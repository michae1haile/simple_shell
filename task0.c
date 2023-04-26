#include <stdlib.h>
#include <unistd.h>

#define MAX_CMD_LENGTH 1024
/**
This is a basic shell that reads user input from standard input using the read function and executes commands 
using the execve function. It also forks a new process for each command entered, and the parent process waits 
for the child to terminate using the waitpid function. Note that this shell does not support any advanced features 
such as input/output redirection or running commands in the background.
*/
int main() {
    char* cmdline = (char*) malloc(MAX_CMD_LENGTH * sizeof(char));
    pid_t pid;
    int status;

    while (1) {
        write(STDOUT_FILENO, ">> ", 3);

        ssize_t nread;
       
          nread	= read(STDIN_FILENO, cmdline, MAX_CMD_LENGTH);
        if (nread == 0) {
            write(STDOUT_FILENO, "\n", 1);
            break;
        }
        else if (nread < 0) {
            perror("read");
            continue;
        }

        
        if (cmdline[nread-1] == '\n') {
            cmdline[nread-1] = '\0';
            nread--;
        }

        
        pid = fork();

        if (pid < 0) {
            perror("fork");
            continue;
        }

        if (pid == 0) {
            
            if (execve(cmdline, NULL, NULL) < 0) {
                perror("execve");
                _exit(1);
            }
        }
        else {
            
            waitpid(pid, &status, 0);
        }
    }

    free(cmdline);
    return 0;
}
