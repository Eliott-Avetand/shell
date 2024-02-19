/*
** EPITECH PROJECT, 2020
** history_list.c
** File description:
** Builtin history
*/

#include "shell.h"

int get_history_len(history_t *history)
{
    history_t *current = history;
    int nbr = 0;

    while (current != NULL) {
        nbr++;
        current = current->next;
    }
    return nbr;
}

history_t *create_history_node(char *clear_line, int cmd_idx)
{
    history_t *node = malloc(sizeof(history_t));
    time_t time_sec = time(NULL);
    struct tm *real_time = localtime(&time_sec);

    if (!node)
        return NULL;
    node->cmd_index = cmd_idx;
    node->command = strdup(clear_line);
    node->minutes = real_time->tm_min;
    node->hours = real_time->tm_hour;
    node->next = NULL;
    node->prev = NULL;
    if (!node->command)
        return NULL;
    return node;
}

int push_in_history(history_t **head, char *line)
{
    history_t *current = (*head);

    if (!line)
        return -1;
    if (!(*head)) {
        (*head) = create_history_node(line, 1);
        if (!(*head))
            return -1;
    } else {
        while (current->next != NULL)
            current = current->next;
        current->next = create_history_node(line, current->cmd_index + 1);
        current->next->prev = current;
        if (!current->next)
            return -1;
    }
    return 0;
}