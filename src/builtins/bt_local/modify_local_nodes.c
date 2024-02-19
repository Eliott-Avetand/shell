/*
** EPITECH PROJECT, 2020
** modify_local_nodes.c
** File description:
** Handle local variables structure
*/

#include "shell.h"

void free_local_node(mylocal_t *node)
{
    free(node->key);
    free(node->value);
    free(node->full_line);
    free(node);
}

char *get_value_by_key_local(mylocal_t *mylocal, char *key)
{
    mylocal_t *current = mylocal;

    while (current != NULL) {
        if (my_strcmp(current->key, key) == 0)
            return current->value;
        current = current->next;
    }
    return NULL;
}

mylocal_t *get_node_by_key_local(mylocal_t *mylocal, char *key)
{
    mylocal_t *current = mylocal;

    while (current != NULL) {
        if (my_strcmp(current->key, key) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}

int modify_value_from_key_local(mylocal_t *mylocal, char *key, char *value)
{
    mylocal_t *node = get_node_by_key_local(mylocal, key);

    if (!node)
        return 84;
    free(node->value);
    free(node->full_line);
    node->value = my_strdup(value);
    node->full_line = malloc(sizeof(char) * (strlen(key) + strlen(value) + 2));
    if (!node->value || !node->full_line)
        return 84;
    node->full_line[0] = '\0';
    strcat(node->full_line, key);
    strcat(node->full_line, "\t");
    strcat(node->full_line, value);
    return 0;
}

void remove_node_from_key_local(mylocal_t **mylocal, char *key)
{
    mylocal_t *prev = (*mylocal);
    mylocal_t *save = NULL;

    if (prev == NULL)
        return;
    if (strcmp(prev->key, key) == 0) {
        (*mylocal) = (*mylocal)->next;
        return free_local_node(prev);
    }
    while (prev->next != NULL && strcmp(prev->next->key, key) != 0)
        prev = prev->next;
    if (prev->next != NULL) {
        save = prev->next;
        prev->next = save->next;
        free_local_node(save);
    }
}