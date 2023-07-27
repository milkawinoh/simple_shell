
#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include <string.h>
#define LIMIT_INPUT 250
#include <unistd.h>

/**
 * 
 * prompt -display a prompt to stdin.
 * Return: on success pointer to the command.
 **/

char *prompt(void)
{
    char *lineptr = NULL;
    size_t n = 0;
    ssize_t result;

    write(1, "$ ", 2);

    result = getline(&lineptr, &n, stdin);

    if (result == -1)
    {
        free(lineptr);
        return NULL;
    }

    if (lineptr[result - 1] == '\n')
    {
        lineptr[result - 1] = '\0';
    }

    return lineptr;
}


/**
 * tokenize - Tokenizes a string.
 * @str: The string to be tokenized.
 * @delimiters: The delimiter used to split the string into tokens.
 *
 * Return: Pointer to an array of tokenized tokens.
 */
char **tokenize(const char *str, const char *delimiters)
{
    size_t num_tokens = 0;
    char **tokens = NULL;
    char *token;
    char *str_copy;
    char *saveptr;
    char **new_tokens ;

    if (str == NULL)
    {
        return NULL;
    }

    str_copy = _strdup(str);
    if (str_copy == NULL)
    {
        perror("Failed to allocate memory");
        return NULL;
    }

    token = strtok_r(str_copy, delimiters, &saveptr);
    while (token != NULL)
    {
        num_tokens++;
        new_tokens = (char **)malloc(sizeof(char *) * (num_tokens + 1));
        if (new_tokens == NULL)
        {
            perror("Failed to allocate memory");
            free(str_copy);
            return NULL;
        }

        for (size_t i = 0; i < num_tokens - 1; i++)
        {
            new_tokens[i] = tokens[i];
        }

        new_tokens[num_tokens - 1] = _strdup(token);
        new_tokens[num_tokens] = NULL; 
        free(tokens);
        tokens = new_tokens;

        token = strtok_r(NULL, delimiters, &saveptr);
    }

    free(str_copy);
    return tokens;
}

