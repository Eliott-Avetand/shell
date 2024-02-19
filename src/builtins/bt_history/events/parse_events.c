/*
** EPITECH PROJECT, 2021
** parse_events.c
** File description:
** parse events
*/

#include "shell.h"

int copy_word(char **new_line, char *clear_line, history_t *h_command,
int last_hist)
{
    char *save = get_word_events(h_command, my_getnbr(clear_line), last_hist);

    strcat((*new_line), save);
    return strlen(save);
}

void handle_words_events(history_t *h_command, char *line, char *new_line,
int *idx)
{
    for (int i = 0; line[i]; i++) {
        if (line[i] == '!' && line[i + 1] >= '0' && line[i + 1] <= '9') {
            (*idx) += copy_word(&new_line, line + (i + 1), h_command, 0);
            i += count_digits(my_getnbr(line + (i + 1)));
        } else if (line[i] == '!' && line[i + 1] == '!') {
            (*idx) += copy_word(&new_line, line, h_command, 1);
            i += 1;
        } else {
            new_line[(*idx)] = line[i];
            (*idx)++;
            new_line[(*idx)] = '\0';
        }
    }
}

char *parse_events(char *line, history_t *h_command)
{
    char *new_line = malloc(sizeof(char) * (get_events_len(line,
    h_command) + strlen(line) + 1));
    int idx = 0;

    if (!new_line)
        return NULL;
    new_line[0] = '\0';
    handle_words_events(h_command, line, new_line, &idx);
    new_line[idx] = '\0';
    free(line);
    return new_line;
}