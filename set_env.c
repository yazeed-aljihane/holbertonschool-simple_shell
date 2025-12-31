#include "shell.h"




int set_env(info_t *info)
{
	int i, j;
	char **tmp_env, *newelm, *val;
	if (info->args[3] != NULL)
	{
		fprintf(stderr, "%s: %d: %s: too many arguments\n",
		info->prog_name, info->line_count, info->args[1]);
		return (-1);
	}
	val = (info->args[2] != NULL) ? info->args[2] : "";

	if (info->args[1] == NULL || info->args[2] == NULL)
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
		newelm = malloc(strlen(info->args[1]) + strlen(val) + 2);
		if (newelm == NULL)
			return (-1);
		sprintf(newelm, "%s=%s", info->args[1], val);
		free(info->env[i]);
		info->env[i] = newelm;
		return(0);
		}
	}
	for (i = 0; info->env[i] != NULL; i++)
		;

	tmp_env = malloc((i + 2) * sizeof(char*));
	if (tmp_env == NULL)
		return (-1);

	for (j = 0; j < i; j++)
		tmp_env[j] = info->env[j];

	newelm = malloc(strlen(info->args[1]) + strlen(val) + 2);
	sprintf(newelm, "%s=%s", info->args[1], val);
	tmp_env[i] = newelm;
	tmp_env[i + 1] = NULL;
	free(info->env);
	info->env = tmp_env;
	return (0);
}




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
			return(0);
		}
	}
return (0);
}



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
