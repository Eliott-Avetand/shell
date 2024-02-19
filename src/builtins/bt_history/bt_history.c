/*
** EPITECH PROJECT, 2020
** bt_history.c
** File description:
** Builtin history
*/

#include "shell.h"

void free_history_node(history_t *head)
{
    history_t *current = NULL;

    current = head->next;
    head->next = current->next;
    free(current->command);
    free(current);
}

void free_history_list(history_t *head)
{
    history_t *current;

    while (head != NULL) {
        current = head;
        head = head->next;
        free(current->command);
        free(current);
    }
    free(head);
}

void check_history_list(history_t **history, char *clear_line)
{
    history_t *current = (*history);

    if (!current)
        return;
    if (strcmp(current->command, clear_line) == 0) {
        (*history) = current->next;
        free(current->command);
        free(current);
        return;
    }
    while (current->next != NULL) {
        if (strcmp(current->next->command, clear_line) == 0) {
            free_history_node(current);
            return;
        }
        current = current->next;
    }
}

void bt_history(data_t *data, char **args)
{
    history_t *tmp = data->lists->history;
    int ac = word_array_len(args);

    if (check_history_error(args) == -1)
        return;
    if (ac >= 2) {
        print_part_history(data, args);
        return;
    }
    print_history(tmp);
    return;
}