/*
** EPITECH PROJECT, 2020
** history_error.c
** File description:
** history error
*/

#include "shell.h"

int check_each_args(char **args)
{
    if (args[1][0] != '-') {
        if (my_str_isnumber(args[1]) == 0) {
            fprintf(stderr, "history: Badly formed number\n");
            return -1;
        } else
            return 0;
    }
    return 0;
}

int check_history_error(char **args)
{
    int ac = word_array_len(args);

    if (ac >= 4) {
        fprintf(stderr, "history: Too many arguments.\n");
        return -1;
    } else if (ac < 2)
        return 0;
    if (check_each_args(args) == -1)
        return -1;
    return 0;
}