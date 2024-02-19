/*
** EPITECH PROJECT, 2020
** my_getline.c
** File description:
** Read user input
*/

#include "shell.h"

char *my_getline(char **line, int opt)
{
    size_t size = 0;
    int read_size;

    (*line) = NULL;
    read_size = getline(line, &size, stdin);
    if (read_size == -1) {
        free((*line));
        if (opt == 1)
            my_putstr("exit\n");
        return NULL;
    }
    (*line)[read_size - opt] = '\0';
    return (*line);
}