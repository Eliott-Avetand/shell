/*
** EPITECH PROJECT, 2020
** modify_alias_list.c
** File description:
** Handle modification of alias list
*/

#include "shell.h"

void modify_or_push_alias(data_t *data, char *key, char *value)
{
    if (get_alias_by_key(data->lists->alias, key) == NULL) {
        if (push_alias_node(data, key, value) == -1)
            return print_error("alias", INTERNAL_ERR, 1);
    } else {
        if (modify_alias_from_key(data->lists->alias, key, value) == -1)
            return print_error("alias", INTERNAL_ERR, 1);
    }
}

int modify_alias_from_key(alias_t *head, char *key, char *value)
{
    alias_t *node = get_alias_by_key(head, key);

    if (!node)
        return -1;
    free(node->value);
    node->value = my_strdup(value);
    if (!node->value)
        return -1;
    return 0;
}

void remove_alias_from_key(alias_t **head, char *key)
{
    alias_t *prev = (*head);
    alias_t *save = NULL;

    if (prev == NULL)
        return;
    if (strcmp(prev->key, key) == 0) {
        (*head) = (*head)->next;
        free(prev->key);
        free(prev->value);
        return free(prev);
    }
    while (prev->next != NULL && strcmp(prev->next->key, key) != 0)
        prev = prev->next;
    if (prev->next != NULL) {
        save = prev->next;
        prev->next = save->next;
        free(save->key);
        free(save->value);
        free(save);
    }
}
