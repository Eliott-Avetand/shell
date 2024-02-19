/*
** EPITECH PROJECT, 2020
** replace_in_backticks.c
** File description:
** Replace the value in the backticks by another string
*/

#include "shell.h"

char *replace_in_backticks(char *full_line, char *results)
{
    int size = get_size_subcommand(full_line) + 2;
    char *new_command = malloc(sizeof(char) *
    (strlen(full_line) - size + strlen(results) + 1));
    int offset = 0;

    while (full_line[offset] != '`')
        offset++;
    strncpy(new_command, full_line, offset);
    new_command[offset] = '\0';
    strcat(new_command, results);
    strcat(new_command, full_line + (offset + size));
    return new_command;
}