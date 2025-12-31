#include "shell.h"


char *_strdup(const char *str)
{
    char *new_str;
    int len = 0;

    if (str == NULL)
        return (NULL);
    while (str[len])
        len++;
    new_str = malloc(sizeof(char) * (len + 1));
    if (!new_str)
        return (NULL);
    for (len = 0; str[len]; len++)
        new_str[len] = str[len];
    new_str[len] = '\0';
    return (new_str);
}

void populate_env_list(info_t *info, char **env)
{
    int i = 0;

    while (env[i])
        i++;

    info->env = malloc(sizeof(char *) * (i + 1));
    if (!info->env)
        return;

    for (i = 0; env[i]; i++)
    {
        info->env[i] = _strdup(env[i]);
    }
    info->env[i] = NULL;
}
