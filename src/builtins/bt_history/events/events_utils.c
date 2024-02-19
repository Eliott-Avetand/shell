/*
** EPITECH PROJECT, 2021
** events_utils.c
** File description:
** events handler
*/

#include "shell.h"

char *get_word_events(history_t *h_command, int nbr_events, int last_events)
{
    history_t *current = h_command;

    if (last_events == 1 && !current)
        return NULL;
    while (current != NULL) {
        if (last_events == 1 && current->next == NULL)
            return current->command;
        if (nbr_events == current->cmd_index)
            return current->command;
        current = current->next;
    }
    return NULL;
}

int nbr_events(char *line)
{
    int nbr = 0;

    for (int i = 0; line[i]; i++) {
        if (line[i] == '!' && line[i + 1] >= '0' && line[i + 1] <= '9')
            nbr++;
    }
    return nbr;
}

int get_events_len(char *line, history_t *h_command)
{
    int len = 0;

    for (int i = 0; line[i]; i++) {
        if (line[i] == '!' && line[i + 1] >= '0' && line[i + 1] <= '9')
            len += strlen(get_word_events(h_command, atoi(line + i + 1), 0));
        else if (line[i] == '!' && line[i + 1] == '!')
            len += strlen(get_word_events(h_command, -1, 1));
    }
    return len;
}