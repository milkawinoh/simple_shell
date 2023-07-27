#include "shell.h"
#include <stdlib.h>


/**
 * _strlen -calculates the length of string pointed by s1.
 * @s : string.
 *@Return - return 0 on success.
 *
 **/

int _strlen(const char *s)

{   
    int count = 0;
    if(s == NULL)
    {
        return 0;
    }
    while ( *s!= '\0')
    {
        count++;
        s++;
    }
    return count;
    
   
}


/**
 * 
 * _strcpy -copy string from source to destination.
 * @dest : destination.
 * @src : source string.
 * Return - pointer to destination string.
 * 
 * */

    char *_strcpy(char *dest, const char *src)
{
    size_t i = 0;
        
    if (dest == NULL || src == NULL)
        {
        return NULL;
        }
    while(src[i] != '\0')
        {
           
            dest[i] = src[i];
            
        }

    dest[i] = '\0';

    return dest;
}
    


/**
 * _strcmp - Compare two strings.
 * @s1: The first string to compare.
 * @s2: The second string to compare.
 *
 * Return: An integer less than, equal to, or greater than zero if s1 is found,
 * respectively, to be less than, to match, or be greater than s2.
 */
int _strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s2)
    {
        if (*s1 != *s2)
        {
            return (*s1 - *s2);
        }
        s1++;
        s2++;
    }

    if (*s1)
    {
        return 1;
    }
    else if (*s2)
    {
        return -1;
    }

    return 0;
}


/**
 * _strcat - Concatenates two strings.
 * @dest: The destination string.
 * @src: The source string to be appended.
 *
 * Return: Pointer to the resulting string (dest).
 */


char *_strcat(char *dest, const char *src)
{
    int i;
    int dest_len = 0;
    int src_len = 0;

    /* Find the length of dest */
    while (dest[dest_len] != '\0')
        dest_len++;

    /* Find the length of src */
    while (src[src_len] != '\0')
        src_len++;

    /* Append src to dest */
    for (i = 0; i <= src_len; i++)
    {
        dest[dest_len + i] = src[i];
    }

    return dest;

}

#include <stdlib.h>
#include <string.h>

/**
 * _strdup - Duplicates a string.
 * @s: The string to duplicate.
 *
 * Return: Pointer to the newly allocated duplicated string.
 *         NULL if memory allocation fails or if s is NULL.
 */
char *_strdup(const char *s)
{
     size_t len;
    if (s == NULL)
        return NULL;

     len = _strlen(s);
    char *new_str = (char *)malloc(len + 1);

    if (new_str == NULL)
        return NULL;

    strcpy(new_str, s);
    return new_str;
}
