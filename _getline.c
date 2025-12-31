#include "shell.h"

#define BUFFER_SIZE 1024

/**
 * _getline - Reads a line from STDIN using a buffer
 *
 * Description: managing a static buffer to minimize read calls.
 * It reallocates memory dynamically as the line grows.
 * Handles EOF and potential read errors gracefully.
 *
 * Return: Pointer to the line string, or NULL on failure/EOF
 */
char *_getline(void)
{
	static char buffer[BUFFER_SIZE];
	static int buf_pos, buf_size;
	char *line = NULL, *new_line, c;
	int len = 0;

	while (1)
	{
		if (buf_pos >= buf_size) /* Refill the buffer if needed */
		{	/* Read new data into the buffer */
			buf_size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			buf_pos = 0; /* Reset buffer position */
			if (buf_size <= 0)
			{
				if (line)
				{
					line[len] = '\0';
					return (line);
				}
				free(line);
				return (NULL);
			}
		}
		c = buffer[buf_pos]; /* Get the next character from the buffer */
		buf_pos++;
		/* Resize line buffer to accommodate new character */
		new_line = _realloc(line, len, len + 2);
		if (!new_line) /* Handle realloc failure */
		{
			free(line);
			return (NULL);
		}
		line = new_line; /* Update line pointer after realloc */
		line[len] = c; /* Store the character */
		len++;
		if (c == '\n') /* Check for newline character */
		{
			line[len] = '\0';
			return (line);
		}
	}
}

/**
 * _realloc - Reallocates a memory block
 * @ptr: Pointer to the previously allocated memory
 * @old_size: Size of the previously allocated memory
 * @new_size: Size of the new memory block
 *
 * Return: Pointer to the reallocated memory block, or NULL on failure
 */
void *_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void *new_ptr; /* Pointer to the new memory block */

	if (new_size == old_size)
		return (ptr);

	/* Handle the case where the new size is zero */
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);

	if (ptr != NULL)
	{
		/* Copy the data from the old block to the new block */
		memcpy(new_ptr, ptr, old_size < new_size ? old_size : new_size);
		free(ptr);
	}

	return (new_ptr);
}

/**
 * _strcmp - Compares two strings
 * @s1: First string
 * @s2: Second string
 *
 * Return: 0 if equal, positive or negative value based on comparison
 */
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
