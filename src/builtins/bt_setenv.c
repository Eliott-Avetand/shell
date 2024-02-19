/*
** EPITECH PROJECT, 2020
** bt_setenv.c
** File description:
** Builtin setenv
*/

#include "shell.h"

int str_isvalid(char *str)
{
    if (!((str[0] >= 65 && str[0] <= 90) ||
    (str[0] >= 97 && str[0] <= 122) || str[0] == '_')) {
        print_error("setenv", SETENV_LTRFIRST, 1);
        return -1;
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if (!((str[i] >= 65 && str[i] <= 90) || str[i] == '_' ||
        (str[i] >= 97 && str[i] <= 122) || (str[i] >= 48 && str[i] <= 57))) {
            print_error("setenv", SETENV_NONALPHA, 1);
            return -1;
        }
    }
    return 0;
}

void add_key_to_myenv(data_t *data, char *key, char *value)
{
    char *full_line;

    if (get_value_by_key(data->lists->env, key) != NULL)
        modify_value_from_key(data->lists->env, key, value);
    else {
        full_line = concat_two_string(key, value, "=");
        if (!full_line)
            return print_error("setenv", INTERNAL_ERR, 1);
        push_in_myenv(&data->lists->env, full_line);
        free(full_line);
        data->exit = 0;
    }
}

void bt_setenv(data_t *data, char **args)
{
    int ac = word_array_len(args);
    char *new_value = (ac > 2) ? args[2] : "\0";

    if (ac == 1)
        return bt_env(data, args);
    if (ac > 3)
        return print_error("setenv", "Too many arguments.\n", 1);
    if (str_isvalid(args[1]) != 0)
        return;
    add_key_to_myenv(data, args[1], new_value);
    if (my_strcmp(args[1], "PATH") == 0) {
        free_path_list(data->lists->path);
        fill_path_list(&data->lists->path, data->lists->env);
    }
    free_tab(data->env_arr);
    data->env_arr = myenv_to_word_array(data->lists->env);
    data->exit = 0;
}