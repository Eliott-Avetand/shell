/*
** EPITECH PROJECT, 2020
** clean_delim.c
** File description:
** Clean delimitor from user input
*/

#include "shell.h"

int is_good_redir(char *arg, int *i)
{
    int good_redir = 0;
    int start_idx = *i + 1;

    (*i) += (arg[*i] == '\0') ? 0 : 1;
    while (arg[*i] != '\0' && arg[*i] != ';') {
        if (((arg[*i - 1] == '>' && arg[*i] == '>') ||
        (arg[*i - 1] == '<' && arg[*i] == '<')) && *i == start_idx)
            (*i)++;
        if (arg[*i] == '|' || arg[*i] == '>' || arg[*i] == '<') {
            fprintf(stderr, "Ambiguous output redirect.\n");
            return 0;
        }
        if (is_delim(arg[*i]) == 0 && arg[*i] != ' ' && arg[*i] != '\0')
            good_redir = 1;
        (*i)++;
    }
    (*i)--;
    if (good_redir == 0)
        fprintf(stderr, "Missing name for redirect.\n");
    return good_redir;
}

int is_good_pipe(char *arg, int *i)
{
    int good_pipe = 0;

    (*i) += (arg[*i] == '\0') ? 0 : 1;
    (*i) += (arg[*i] == '|') ? 1 : 0;
    while (arg[*i] != '\0' && arg[*i] != '|') {
        if (is_delim(arg[*i]) == 0 && arg[*i] != ' ')
            good_pipe = 1;
        (*i)++;
    }
    (*i)--;
    return good_pipe;
}

int check_invalid_redirection(char *arg)
{
    int ltr = 0;

    for (int i = 0; arg[i] != '\0'; i++) {
        if (is_delim(arg[i]) == 0 && arg[i] != ' ')
            ltr = 1;
        if (((arg[i] == '|' || arg[i] == '>' || arg[i] == '<') && ltr == 0) ||
        (arg[i] == '|' && is_good_pipe(arg, &i) == 0)) {
            fprintf(stderr, "Invalid null command.\n");
            return -1;
        }
        if ((arg[i] == '>' || arg[i] == '<') && is_good_redir(arg, &i) == 0)
            return -1;
    }
    return 0;
}

void avoid_delim(char *arg, char *str, int *i, int *co)
{
    if ((arg[*i] == '>' && arg[*i + 1] == '>') || (arg[*i] == '<' &&
    arg[*i + 1] == '<') || (arg[*i] == '|' && arg[*i + 1] == '|'))
        str[(*co)++] = arg[(*i)++];
    while (is_delim(arg[*i]) == 1)
        (*i)++;
    if (is_delim(arg[*i]) == 0 && arg[*i] != '\0')
        (*i)--;
    str[(*co)++] = arg[*i];
}

char *clean_delim(char *arg)
{
    char *str = malloc(sizeof(char) * my_strlen(arg) + 1);
    int ltr = 0;
    int co = 0;

    if (!str)
        return NULL;
    for (int i = 0; arg[i] != '\0'; i++) {
        if (is_delim(arg[i]) == 0) {
            str[co++] = arg[i];
            ltr = 1;
        } else if (arg[i + 1] != '\0' && ltr == 1)
            avoid_delim(arg, str, &i, &co);
    }
    str[co] = '\0';
    return str;
}