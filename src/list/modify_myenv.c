/*
** EPITECH PROJECT, 2020
** modify_myenv.c
** File description:
** Contains functions to modify (or get) info from my_env
*/

#include "shell.h"

char *get_value_by_key(myenv_t *myenv, char *key)
{
    myenv_t *current = myenv;

    while (current != NULL) {
        if (my_strcmp(current->key, key) == 0)
            return current->value;
        current = current->next;
    }
    return NULL;
}

myenv_t *get_node_by_key(myenv_t *myenv, char *key)
{
    myenv_t *current = myenv;

    while (current != NULL) {
        if (my_strcmp(current->key, key) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}

int modify_value_from_key(myenv_t *myenv, char *key, char *value)
{
    myenv_t *node = get_node_by_key(myenv, key);

    if (!node)
        return 84;
    free(node->value);
    free(node->full_line);
    node->value = strdup(value);
    node->full_line = concat_two_string(key, value, "=");
    if (!node->value || !node->full_line)
        return 84;
    return 0;
}

void remove_node_from_key(myenv_t **myenv, char *key)
{
    myenv_t *prev = (*myenv);
    myenv_t *save = NULL;

    if (prev == NULL)
        return;
    if (strcmp(prev->key, key) == 0) {
        (*myenv) = (*myenv)->next;
        return free_env_node(prev);
    }
    while (prev->next != NULL && strcmp(prev->next->key, key) != 0)
        prev = prev->next;
    if (prev->next != NULL) {
        save = prev->next;
        prev->next = save->next;
        free_env_node(save);
    }
}