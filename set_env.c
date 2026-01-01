#include "shell.h"

/**
 * set_env - Initialize a new environment variable or modify an existing one
 * @info: Structure containing potential arguments.
 * Return: 0 on success, -1 on failure
 */
int set_env(info_t *info)
{
	int i;
	char *new_elm, *val;

	if (info->args[3] != NULL)
	{
		fprintf(stderr, "%s: %d: %s: too many arguments\n",
			info->prog_name, info->line_count, info->args[1]);
		return (-1);
	}
	if (info->args[1] == NULL)
	{
		fprintf(stderr, "%s: %d: %s: too few arguments\n",
			info->prog_name, info->line_count, info->args[0]);
		return (-1);
	}

	val = (info->args[2]) ? info->args[2] : "";
	new_elm = create_env_string(info->args[1], val);
	if (new_elm == NULL)
		return (-1);

	for (i = 0; info->env[i]; i++)
	{
		if (strncmp(info->env[i], info->args[1], strlen(info->args[1])) == 0
		    && info->env[i][strlen(info->args[1])] == '=')
		{
			free(info->env[i]);
			info->env[i] = new_elm;
			return (0);
		}
	}
	return (_add_env_node(info, new_elm));
}



/**
 * unset_env - removes an environment variable
 * @info: the parameter struct
 *
 * Return: 0 on success, -1 on error
 */
int unset_env(info_t *info)
{
	int i, j, k;

	if (info->args[3] != NULL)
	{
		fprintf(stderr, "%s: %d: %s: too many arguments\n",
		info->prog_name, info->line_count, info->args[0]);
		return (-1);
	}
	if (info->args[1] == NULL)
	{
		fprintf(stderr, "%s: %d: %s: too few arguments\n",
		info->prog_name, info->line_count, info->args[0]);
		return (-1);
	}
	for (j = 0; info->args[1][j] != '\0'; j++)
		;
	for (i = 0; info->env[i] != NULL; i++)
	{
		if (strncmp(info->env[i], info->args[1], j) == 0 && info->env[i][j] == '=')
		{
			free(info->env[i]);
			for (k = i; info->env[k] != NULL; k++)
			{
				info->env[k] = info->env[k + 1];
			}
			return (0);
		}
	}
return (0);
}


/**
 * free_env - frees the environment variable list
 * @info: the parameter struct
 *
 * Return: void
 */
void free_env(info_t *info)
{
	int i;

	if (info->env == NULL)
		return;

	for (i = 0; info->env[i] != NULL; i++)
	{
		free(info->env[i]);
	}

	free(info->env);

	info->env = NULL;
}

/**
 * create_env_string - creates a "name=value" string
 * @name: variable name
 * @value: variable value
 * Return: pointer to new string or NULL
 */
char *create_env_string(char *name, char *value)
{
	char *new_str;
	size_t len;

	len = strlen(name) + strlen(value) + 2;
	new_str = malloc(len);
	if (new_str == NULL)
		return (NULL);
	sprintf(new_str, "%s=%s", name, value);
	return (new_str);
}


/**
 * _add_env_node - adds a new variable to the env array
 * @info: structure containing arguments
 * @new_elm: the new string to add
 * Return: 0 on success, -1 on failure
 */
int _add_env_node(info_t *info, char *new_elm)
{
	char **tmp_env;
	int i;

	for (i = 0; info->env[i] != NULL; i++)
		;
	tmp_env = malloc((i + 2) * sizeof(char *));
	if (tmp_env == NULL)
	{
		free(new_elm);
		return (-1);
	}
	for (i = 0; info->env[i] != NULL; i++)
		tmp_env[i] = info->env[i];
	tmp_env[i] = new_elm;
	tmp_env[i + 1] = NULL;
	free(info->env);
	info->env = tmp_env;
	return (0);
}
