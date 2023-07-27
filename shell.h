#ifndef SHELL_H
#define SHELL_H

#include <stddef.h>
#include <limits.h>



char *prompt(void);
char **tokenize(const char *str, const char *delimiters);
int execute(const char *av, char **argv, char **dir_tokens);
char *compare_path(const char *cmd, char **dir_tokens);
char **getpath(void);
void print_environment(void);


int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
int _strcmp(const char *s1, const char *s2);
char *_strdup(const char *s);



#endif /* SHELL_H */

