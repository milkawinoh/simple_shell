
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ; /* The external environment variable pointer */

/**
 * _getenv - Get the value of an environment variable.
 * @name: The name of the environment variable to find.
 *
 * Return: The value of the environment variable, or NULL if not found.
 */
char *_getenv(const char *name)

{
    char **env;
    size_t name_len;
    char *value = NULL;
	if (name == NULL || environ == NULL)
	{
		return NULL; /* Invalid input or environment variable not set */
	}

	name_len = _strlen(name);
	

	for (env = environ; *env != NULL; env++)
	{
		if (_strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
		{
			value = *env + name_len + 1; /* Point to the value part after '=' */
			break;
		}
	}

	return value;
}

