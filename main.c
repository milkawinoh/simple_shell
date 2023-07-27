#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include "shell.h"
#include <unistd.h>
#include <sys/wait.h> 

int main(void)
{
    char *cmd = NULL;
    char **av = NULL;
    char **dir_tokens = NULL;
    size_t i;

    dir_tokens = getpath();
    if (dir_tokens == NULL)
    {
        perror("Failed to get PATH");
        return 1;
    }

    while (1)
    {
        cmd = prompt();

        if (cmd == NULL)
        {
            perror("INVALID COMMAND");
            continue;
        }

        av = tokenize(cmd, " ");
        if (av == NULL)
        {
            free(cmd);
            continue;
        }

        if (_strcmp(av[0], "exit") == 0)
        {
            free(cmd);
            free(av);
            break;
        }
       else
        {
            int status;
            pid_t pid = fork();
            if (pid == -1)
            {
                perror("fork failed");
                exit(EXIT_FAILURE);
            }
            else if (pid == 0)
            {
                char *full_path = compare_path(av[0], dir_tokens);
                if (full_path != NULL)
                {
                    execv(full_path, av);
                    perror("execute failed");
                    free(full_path);
                    free(cmd);
                    free(av);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    free(cmd);
                    free(av);
                    exit(EXIT_SUCCESS);
                }
            }
            else
            {
                waitpid(pid, &status, 0);
            }
        }

        free(cmd);
        free(av);
    }

    for (i = 0; dir_tokens[i] != NULL; i++)
    {
        free(dir_tokens[i]);
    }
    free(dir_tokens);

    return 0;
}

