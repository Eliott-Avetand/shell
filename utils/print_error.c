/*
** EPITECH PROJECT, 2020
** print_strings.c
** File description:
** Print strings and errors
*/

#include "shell.h"

int my_perror(char *prefix, int exit_code)
{
    data_t *data = get_sh();

    if (!data)
        return 1;
    fprintf(stderr, "%s: %s.\n", prefix, strerror(errno));
    data->exit = exit_code;
    return exit_code;
}

void print_error(char *prefix, char *err, int exit_code)
{
    data_t *data = get_sh();

    if (!data)
        return;
    if (err) {
        if (prefix)
            fprintf(stderr, "%s: %s", prefix, err);
        else
            fprintf(stderr, "%s", err);
    }
    data->exit = exit_code;
}