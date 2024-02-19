/*
** EPITECH PROJECT, 2021
** print_prompt.c
** File description:
** Print the prompt
*/

#include "shell.h"

data_t *sh_manager(void *ptr, int mode)
{
    static data_t *sh = NULL;

    if (mode == 1)
        sh = ptr;
    return sh;
}

void set_sh(data_t *ptr)
{
    sh_manager(ptr, 1);
}

data_t *get_sh(void)
{
    return sh_manager(NULL, 0);
}

void print_prompt(data_t *data)
{
    char *log_name;
    char *dir_name;

    if (isatty(STDIN_FILENO) == 0)
        return;
    log_name = get_value_by_key(data->lists->env, "LOGNAME");
    dir_name = get_directory_name();
    if (!log_name || !dir_name)
        my_putstr("[42sh]$ ");
    else {
        my_printf("[%s@42sh %s]$ ", log_name, dir_name);
        free(dir_name);
    }
}