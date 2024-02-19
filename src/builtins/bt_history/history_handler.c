/*
** EPITECH PROJECT, 2020
** history_handler.c
** File description:
** Builtin history
*/

#include "shell.h"

void print_history(history_t *history)
{
    history_t *current = history;
    int len_nbr = 0;

    while (current != NULL) {
        len_nbr = count_digits(current->cmd_index);
        for (int j = len_nbr; j < 6; j++)
            write(1, " ", 1);
        if (current->minutes <= 0) {
            printf("%d  %d:00  %s\n", current->cmd_index,
            current->hours, current->command);
        } else if (current->minutes < 10) {
            printf("%d  %d:0%d  %s\n", current->cmd_index, current->hours,
            current->minutes, current->command);
        } else
            printf("%d  %d:%d  %s\n", current->cmd_index, current->hours,
            current->minutes, current->command);
        current = current->next;
    }
}

void print_part_history(data_t *data, char **args)
{
    history_t *current = data->lists->history;
    int nbr_to_print = get_history_len(data->lists->history) - atoi(args[1]);

    if (nbr_to_print <= 0)
        return print_history(current);
    while (current != NULL && nbr_to_print != 0) {
        nbr_to_print--;
        current = current->next;
    }
    print_history(current);
}