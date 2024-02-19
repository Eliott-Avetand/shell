/*
** EPITECH PROJECT, 2020
** str_utils.c
** File description:
** Contains utils functions for strings
*/

#include "shell.h"

int my_str_contains(char *str, char c)
{
    int co = 0;

    for (int i = 0; str[i] != '\0'; i++)
        co += (str[i] == c) ? 1 : 0;
    return co;
}

int my_str_isnumber(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] < '0' || str[i] > '9') && str[i] != '-')
            return 0;
    }
    return 1;
}

char *analyse_first_arg(data_t *data, command_t *cmd)
{
    char *pwd = get_value_by_key(data->lists->env, "PWD");
    char *path = NULL;

    if (word_array_contains(data->builtins, cmd->args[0]) == 1 ||
        is_echo_builtin(cmd->args) == 1) {
        cmd->type = BUILTIN;
        return NULL;
    }
    if (cmd->args[0][0] == '.' && cmd->args[0][1] == '/')
        path = search_in_pwd(pwd, cmd->args[0]);
    else
        path = search_in_mypath(data->lists->path, cmd->args[0]);
    cmd->type = (path) ? BIN : NOT_FOUND;
    return path;
}

char *concat_two_string(char *str1, char *str2, char *sep)
{
    char *dest;

    if (!str1 || !str2)
        return NULL;
    dest = malloc(sizeof(char) * (strlen(str1) + strlen(str2) + 2));
    if (!dest)
        return NULL;
    dest[0] = '\0';
    strcat(dest, str1);
    if (sep)
        strcat(dest, sep);
    return strcat(dest, str2);
}

char **separate_bin_and_path(char *arg)
{
    char **tab = malloc(sizeof(char *) * 3);
    int co = my_strlen(arg) - 1;

    if (!tab)
        return NULL;
    while (arg[co] != '/')
        co--;
    tab[0] = malloc(sizeof(char) * (co + 1));
    tab[1] = my_strdup(arg + co + 1);
    if (!tab[0] || !tab[1])
        return NULL;
    my_strncpy(tab[0], arg, co);
    tab[2] = NULL;
    return tab;
}