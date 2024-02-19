/*
** EPITECH PROJECT, 2020
** alias_handler.c
** File description:
** Handle alias linked list creation and modification
*/

#include "shell.h"

alias_t *create_alias_node(char *key, char *value)
{
    alias_t *node = malloc(sizeof(alias_t));

    if (!node)
        return NULL;
    node->key = strdup(key);
    node->value = strdup(value);
    node->next = NULL;
    if (!node->key || !node->value)
        return NULL;
    return node;
}

int push_alias_node(data_t *data, char *key, char *value)
{
    alias_t *current = data->lists->alias;

    if (!current) {
        data->lists->alias = create_alias_node(key, value);
        if (!data->lists->commands)
            return 1;
    }
    else {
        while (current->next != NULL)
            current = current->next;
        current->next = create_alias_node(key, value);
        if (!current->next)
            return 1;
    }
    return 0;
}

alias_t *get_alias_by_key(alias_t *head, char *key)
{
    alias_t *current = head;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}

void free_alias_list(alias_t *head)
{
    alias_t *current;

    while (head != NULL) {
        current = head;
        head = head->next;
        free(current->key);
        free(current->value);
        free(current);
    }
}