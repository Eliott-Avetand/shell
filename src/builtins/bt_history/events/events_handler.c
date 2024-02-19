/*
** EPITECH PROJECT, 2021
** events_handler.c
** File description:
** events handler
*/

#include "shell.h"

int events_handler(data_t *data)
{
    if (contains_events(data->clean_input) == 1) {
        if (check_existing_events(data->clean_input,
        data->lists->history) == -1) {
            free(data->clean_input);
            return -1;
        }
        data->clean_input = parse_events(data->clean_input,
        data->lists->history);
        printf("%s\n", data->clean_input);
        return 1;
    }
    return 0;
}

int contains_events(char *clear_line)
{
    for (int i = 0; clear_line[i]; i++) {
        if (clear_line[i] == '!')
            return 1;
    }
    return 0;
}