/*
** EPITECH PROJECT, 2020
** builtins.c
** File description:
** Handle builtin functions
*/

#include "shell.h"

void bt_unsetenv(data_t *data, char **args)
{
    int ac = word_array_len(args);

    if (ac < 2)
        return print_error("unsetenv", "Too few arguments.\n", 1);
    for (int i = 1; args[i] != NULL; i++)
        remove_node_from_key(&data->lists->env, args[i]);
    if (word_array_contains(args, "PATH") == 1) {
        free_path_list(data->lists->path);
        data->lists->path = NULL;
    }
    free_tab(data->env_arr);
    data->env_arr = myenv_to_word_array(data->lists->env);
    data->exit = 0;
}

void bt_env(data_t *data, UNUSED char **args)
{
    myenv_t *current = data->lists->env;

    while (current != NULL) {
        printf("%s\n", current->full_line);
        current = current->next;
    }
    data->exit = 0;
}

void bt_exit(data_t *data, char **args)
{
    int ac = word_array_len(args);

    if (ac > 2)
        return print_error("exit", "Expression Syntax.\n", 1);
    if (ac == 1 && (data->exit == 139 || data->exit == 136))
        data->exit = 0;
    else if (ac == 2) {
        if (my_str_isnumber(args[1]) == 0)
            return print_error("exit", "Badly formed number.\n", 1);
        data->exit = my_getnbr(args[1]) % 256;
    }
    data->is_exited = 1;
}

void handle_builtins(data_t *data, char **args)
{
    void (*ptr[10])(data_t *data, char **args) = {bt_exit, bt_cd, bt_unalias,
    bt_setenv, bt_unsetenv, bt_history, bt_alias, bt_env, bt_set, bt_unset};

    for (int i = 0; data->builtins[i] != NULL; i++) {
        if (my_strcmp(data->builtins[i], args[0]) == 0)
            (*ptr[i])(data, args);
    }
    if (is_echo_builtin(args) == 1)
        bt_echo(data, args);
}