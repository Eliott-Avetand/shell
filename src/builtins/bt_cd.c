/*
** EPITECH PROJECT, 2020
** bt_cd.c
** File description:
** Builtin CD
*/

#include "shell.h"

void set_pwd(data_t *data)
{
    char *act_dir = getcwd(NULL, 0);

    if (!act_dir)
        return print_error(NULL, NULL, 1);
    modify_value_from_key(data->lists->env, "PWD", act_dir);
    free(act_dir);
    free_tab(data->env_arr);
    data->env_arr = myenv_to_word_array(data->lists->env);
    data->exit = 0;
}

void my_chdir(data_t *data, char *path, char *arg)
{
    char *oldpwd = NULL;

    if (!path || path[0] == '\0')
        return print_error(NULL, ": No such file or directory.\n", 1);
    oldpwd = getcwd(NULL, 0);
    if (!oldpwd)
        data->exit = my_perror(arg, 1);
    else if (chdir(path) == -1) {
        data->exit = my_perror(path, 1);
        free(oldpwd);
    } else {
        add_key_to_myenv(data, "OLDPWD", oldpwd);
        set_pwd(data);
        free(oldpwd);
    }
}

void bt_cd(data_t *data, char **args)
{
    int ac = word_array_len(args);

    if (ac == 1)
        my_chdir(data, get_value_by_key(data->lists->env, "HOME"), args[0]);
    else if (ac == 2) {
        if (strcmp(args[1], "-") == 0)
            my_chdir(data, get_value_by_key(data->lists->env,
            "OLDPWD"), args[0]);
        else
            my_chdir(data, args[1], args[0]);
    } else
        print_error("cd", "Too many arguments.\n", 1);
}