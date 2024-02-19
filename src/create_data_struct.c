/*
** EPITECH PROJECT, 2020
** create_data_struct.c
** File description:
** Create data structure for 42sh
*/

#include "shell.h"

void ctrlc_handler(UNUSED int sig)
{
    data_t *data = get_sh();

    my_putchar('\n');
    print_prompt(data);
}

void fill_path_list(mypath_t **path_head, myenv_t *env_head)
{
    char *path_line = get_value_by_key(env_head, "PATH");
    char **folders = NULL;

    if (!path_line)
        return;
    folders = str_to_word_array(path_line, ':');
    if (!folders)
        return;
    for (int i = 0; folders[i] != NULL; i++) {
        if (push_in_mypath(path_head, folders[i]) != 0)
            return;
    }
    free_tab(folders);
}

int fill_env_list(myenv_t **head, char **envp)
{
    for (int i = 0; envp[i] != NULL; i++) {
        if (push_in_myenv(head, envp[i]) != 0)
            return 84;
    }
    return 0;
}

lists_t *init_all_list(char **envp)
{
    lists_t *lists = malloc(sizeof(lists_t));

    if (!lists)
        return NULL;
    lists->env = NULL;
    lists->local = NULL;
    lists->path = NULL;
    lists->commands = NULL;
    lists->history = NULL;
    lists->alias = NULL;
    if (fill_env_list(&lists->env, envp) != 0)
        return NULL;
    fill_path_list(&lists->path, lists->env);
    return lists;
}

data_t *create_data_struct(char **envp)
{
    data_t *data = malloc(sizeof(data_t));

    if (!data)
        return NULL;
    data->exit = 0;
    data->is_exited = 0;
    data->input = NULL;
    data->clean_input = NULL;
    data->lists = init_all_list(envp);
    data->builtins = str_to_word_array(BUILTINS, ' ');
    if (!data->builtins || !data->lists)
        return NULL;
    data->env_arr = myenv_to_word_array(data->lists->env);
    set_sh(data);
    signal(SIGINT, ctrlc_handler);
    return data;
}