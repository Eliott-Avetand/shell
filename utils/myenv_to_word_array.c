/*
** EPITECH PROJECT, 2020
** myenv_to_word_array.c
** File description:
** Convert my_env list to an array of strings
*/

#include "shell.h"

int get_myenv_len(myenv_t *head)
{
    myenv_t *current = head;
    int co = 0;

    while (current != NULL) {
        co++;
        current = current->next;
    }
    return co;
}

char **myenv_to_word_array(myenv_t *head)
{
    myenv_t *current = head;
    int len = get_myenv_len(head);
    char **tab = malloc(sizeof(char *) * (len + 1));

    if (!tab)
        return NULL;
    for (int i = 0; current != NULL; i++) {
        tab[i] = my_strdup(current->full_line);
        if (!tab[i])
            return NULL;
        current = current->next;
    }
    tab[len] = NULL;
    return tab;
}