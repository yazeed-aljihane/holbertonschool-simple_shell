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
		new_line = realloc(line, len + 2);
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
