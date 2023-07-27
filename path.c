#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include "shell.h"
#include <unistd.h>



/**
 * compare_path - Searches for the full path of a command in the directories
 *               listed in the PATH environment variable.
 * @cmd: The command to search for.
 * @dir_tokens: The array of directory tokens from PATH.
 *
 * Return: The full path of the command if found, NULL otherwise.
 */
char *compare_path(const char *cmd, char **dir_tokens)
{
    DIR *dir_stream;
    char *full_path = NULL;
    struct dirent *list;
    size_t i;

    if (cmd[0] == '/') {
        /* Command is already an absolute path, no need to search in PATH */
        if (access(cmd, X_OK) == 0) {
            full_path = _strdup(cmd);
            if (full_path == NULL) {
                perror("Failed to allocate memory to full path");
                return NULL;
            }
        } else {
            perror("Command not found");
        }

        return full_path;
    }

    
    for (i = 0; dir_tokens[i] != NULL; i++)
    {
        dir_stream = opendir(dir_tokens[i]);
        if (dir_stream == NULL)
        {
            continue;
        }

        list = readdir(dir_stream);
        while (list != NULL)
        {
            size_t directory_len = strlen(dir_tokens[i]);
            size_t name_len = strlen(list->d_name);

            full_path = (char *)malloc(directory_len + 1 + name_len + 1);
            if (full_path == NULL)
            {
                perror("Failed to allocate memory to full path");
                closedir(dir_stream);
                return NULL;
            }

            /*Create the full path by concatenating directory and file name*/
            strcpy(full_path, dir_tokens[i]);
            strcat(full_path, "/");
            strcat(full_path, list->d_name);

            if (strcmp(list->d_name, cmd) == 0)
            {
                closedir(dir_stream);
                return full_path;
            }

            free(full_path);
            list = readdir(dir_stream);
        }

        closedir(dir_stream);
    }

    return NULL;
}

/**
 * getpath - Retrieves the directories listed in the PATH environment variable.
 *
 * Return: An array of directory tokens, or NULL if unsuccessful.
 */
char **getpath(void)
{
    char *delimiter = ":";
    char *path_dir;
    char **dir_tokens;

    path_dir = _getenv("PATH");
    if (path_dir == NULL)
    {
        perror("getenv failed");
        return NULL;
    }

    dir_tokens = tokenize(path_dir, delimiter);
    if (dir_tokens == NULL)
    {
        perror("Failed to get PATH");
        return NULL;
    }

    return dir_tokens;
}

