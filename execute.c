#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include "shell.h"

int execute(const char *av, char **argv, char **dir_tokens)
{
    pid_t pid;
    char *full_path = NULL;
    int status = 0;

    if (dir_tokens != NULL)
    {
        full_path = compare_path(av, dir_tokens);
        if (full_path == NULL)
        {
            perror("Command not found");
            return -1;
        }
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        if (dir_tokens != NULL)
        {
            execv(full_path, argv);
            perror("execute failed");
            free(full_path);
            exit(EXIT_FAILURE);
        }
        else
        {
            /* Child process for external commands*/
            execvp(av, argv); 
            perror("execute failed");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        /* Parent process for built-in commands*/
        if (dir_tokens != NULL)
            free(full_path);

        
        wait(&status);
    }

    return status;
}

