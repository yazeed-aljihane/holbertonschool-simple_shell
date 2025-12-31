#include "shell.h"

/**
 * is_delim - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (c == *delim++)
			return (1);
	return (0);
}

/**
 * _strtok - splits a string into words
 * @str: the input string
 * @delim: the delimeter string
 * Return: pointer to next token or NULL
 */
char *_strtok(char *str, char *delim)
{
	static char *backup;
	char *ret;

	if (!str)
		str = backup;

	if (!str)
		return (NULL);

	/* Skip leading delimiters */
	while (*str && is_delim(*str, delim))
		str++;

	if (*str == '\0')
	{
		backup = NULL;
		return (NULL);
	}

	ret = str;

	/* Find the end of the token */
	while (*str)
	{
		if (is_delim(*str, delim))
		{
			*str = '\0';
			backup = str + 1;
			return (ret);
		}
		str++;
	}

	/* No more delimiters, set backup to NULL */
	backup = NULL;
	return (ret);
}
