/*
** EPITECH PROJECT, 2020
** parse_subcommand.c
** File description:
** Parse the command in the backticks
*/

#include "shell.h"

int get_size_subcommand(char *full_line)
{
    int i = 0;
    int size = 0;

    while (full_line[i] != '`')
        i++;
    i++;
    while (full_line[i + size] != '`')
        size++;
    return size;
}

char *parse_subcommand(char *full_line)
{
    int size = get_size_subcommand(full_line);
    char *subcommand = malloc(sizeof(char) * (size + 1));
    int offset = 0;

    while (full_line[offset] != '`')
        offset++;
    offset++;
    strncpy(subcommand, full_line + offset, size);
    subcommand[size] = '\0';
    return subcommand;
}