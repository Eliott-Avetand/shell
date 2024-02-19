/*
** EPITECH PROJECT, 2020
** clean_user_input.c
** File description:
** Clean user input
*/

#include "shell.h"

int is_delim(char c)
{
    for (int i = 0; DELIMS[i]; i++) {
        if (c == DELIMS[i])
            return 1;
    }
    return 0;
}

void avoid_space(char *arg, char *str, int *i, int *co)
{
    int good_space = 0;

    if (is_delim(arg[*i - 1]) == 0)
        good_space = 1;
    while (arg[*i] == ' ')
        (*i)++;
    if (good_space == 1 && is_delim(arg[*i]) == 0)
        (*i)--;
    str[(*co)++] = arg[*i];
}

char *clean_space(char *arg)
{
    char *str = malloc(sizeof(char) * my_strlen(arg) + 1);
    int ltr_before = 0;
    int co = 0;

    if (!str)
        return NULL;
    for (int i = 0; arg[i] != '\0'; i++) {
        if (arg[i] != ' ') {
            ltr_before = 1;
            str[co++] = arg[i];
        } else if (ltr_before == 1)
            avoid_space(arg, str, &i, &co);
    }
    str[co] = '\0';
    return str;
}

int check_unmatched_quote(char *arg)
{
    if (my_str_contains(arg, '\'') % 2 != 0) {
        print_error(NULL, "Unmatched '''.\n", 1);
        return -1;
    }
    if (my_str_contains(arg, '"') % 2 != 0) {
        print_error(NULL, "Unmatched '\"'.\n", 1);
        return -1;
    }
    return 0;
}

char *clean_user_input(char *input)
{
    char *cleaned_space;
    char *cleaned_delim;

    for (int i = 0; input[i] != '\0'; i++)
        input[i] = (input[i] == '\t') ? ' ' : input[i];
    if (check_invalid_redirection(input) != 0 ||
    check_unmatched_quote(input) != 0)
        return NULL;
    cleaned_space = clean_space(input);
    if (!cleaned_space)
        return NULL;
    cleaned_delim = clean_delim(cleaned_space);
    free(cleaned_space);
    if (!cleaned_delim)
        return NULL;
    return cleaned_delim;
}