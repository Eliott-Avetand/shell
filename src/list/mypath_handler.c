/*
** EPITECH PROJECT, 2020
** mypath_handler.c
** File description:
** Handle my_path linked list creation and modification
*/

#include "shell.h"

mypath_t *create_path_node(char *folder)
{
    mypath_t *node = malloc(sizeof(mypath_t));

    if (!node)
        return NULL;
    node->folder = my_strdup(folder);
    node->next = NULL;
    if (!node->folder)
        return NULL;
    return node;
}

int push_in_mypath(mypath_t **head, char *line)
{
    mypath_t *current = (*head);

    if (!current) {
        (*head) = create_path_node(line);
        if (!(*head))
            return -1;
    } else {
        while (current->next != NULL)
            current = current->next;
        current->next = create_path_node(line);
        if (!current->next)
            return -1;
    }
    return 0;
}