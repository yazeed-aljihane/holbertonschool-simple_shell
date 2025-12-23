#include "shell.h"

/**
 * free_info - frees fields of the info_t struct
 * @info: pointer to the info_t struct to be cleared
 *
 * Return: void
 */
void free_info(info_t *info)
{
	if (info->path)
	{
		/* Avoid double free */
		if (info->args || info->path != info->args[0])
			free(info->path);

		info->path = NULL; /* Prevent dangling pointer */
	}

	if (info->args)
	{
		free(info->args);
		info->args = NULL; /* Prevent dangling pointer */
	}

	if (info->line)
	{
		free(info->line);
		info->line = NULL; /* Prevent dangling pointer */
	}
}
