/*
** EPITECH PROJECT, 2020
** cleanup.c
** File description:
** Free all pointers used in 42sh
*/

#include "shell.h"

void free_tab(char **tab)
{
    for (int i = 0; tab[i] != NULL; i++)
        free(tab[i]);
    free(tab);
}

void free_data(data_t *data)
{
    free_env_list(data->lists->env);
    free_local_list(data->lists->local);
    free_path_list(data->lists->path);
    free_history_list(data->lists->history);
    free_alias_list(data->lists->alias);
    free_tab(data->builtins);
    free_tab(data->env_arr);
    free(data->lists);
    free(data);
}

void my_exit(data_t *data)
{
    int exit_code = data->exit;

    free(data->clean_input);
    free(data->input);
    free_command_list(data->lists->commands);
    free_data(data);
    exit(exit_code);
}