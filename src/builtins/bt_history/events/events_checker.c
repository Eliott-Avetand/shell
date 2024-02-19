/*
** EPITECH PROJECT, 2021
** events_handler.c
** File description:
** events handler
*/

#include "shell.h"

int check_other_events(char *line, int *i)
{
    if (line[(*i)] == '!' && line[(*i) + 1] != '!' && line[(*i) + 1] != '\0' &&
    is_delim(line[(*i) + 1]) != 1) {
        while (line[(*i) + 1] != ' ' && line[(*i) + 1] != '\0') {
            fprintf(stderr, "%c", line[(*i) + 1]);
            (*i)++;
        }
        fprintf(stderr, ": Events not found.\n");
        return -1;
    }
    return 0;
}

int check_last_events(char *line, int *i, history_t *history)
{
    int several = 0;

    while (line[(*i)] == '!' && line[(*i) + 1] == '!' &&
    line[(*i) + 1] != '\0') {
        if (get_word_events(history, -1, 1) == NULL) {
            fprintf(stderr, "1: Events not found.\n");
            return -1;
        }
        several++;
        (*i)++;
    }
    if (several > 0)
        (*i)++;
    if (check_other_events(line, i) == -1)
        return -1;
    return 0;
}

int check_events_history(char *line, int *i, history_t *history)
{
    char *events = NULL;
    int nbr_events = 0;

    if (line[(*i)] == '!' && line[(*i) + 1] >= '0' && line[(*i) + 1] <= '9') {
        nbr_events = atoi(line + ((*i) + 1));
        events = get_word_events(history, nbr_events, 0);
        if (!events) {
            fprintf(stderr, "%d: Events not found.\n", nbr_events);
            return -1;
        }
    } else {
        if (check_last_events(line, i, history) == -1)
            return -1;
    }
    return 0;
}

int check_existing_events(char *clear_line, history_t *history)
{
    for (int i = 0; clear_line[i] != '\0'; i++) {
        if (check_events_history(clear_line, &i, history) == -1) {
            return -1;
        }
    }
    return 0;
}