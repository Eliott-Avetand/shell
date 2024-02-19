/*
** EPITECH PROJECT, 2020
** word_array_utils.c
** File description:
** Get length of a word array
*/

#include "shell.h"

int word_array_len(char **tab)
{
    int co = 0;

    if (!tab)
        return -1;
    while (tab[co] != NULL)
        co++;
    return co;
}

int word_array_contains(char **tab, char *str)
{
    for (int i = 0; tab[i] != NULL; i++) {
        if (my_strcmp(tab[i], str) == 0)
            return 1;
    }
    return 0;
}

int total_word_array_len(char **tab)
{
    int len = 0;

    for (int i = 0; tab[i] != NULL; i++)
        len += (int)strlen(tab[i]) + 1;
    return len;
}

char *word_array_to_string(char **tab)
{
    char *str = malloc(sizeof(char) * (total_word_array_len(tab) + 1));

    if (!str)
        return NULL;
    str[0] = '\0';
    for (int i = 0; tab[i] != NULL; i++) {
        strcat(str, tab[i]);
        strcat(str, " ");
    }
    strcat(str, "\0");
    return str;
}