/*
** EPITECH PROJECT, 2020
** myenv_handler.c
** File description:
** Handle my_env linked list creation and modification
*/

#include "shell.h"

char *malloc_env_key(char *str, int *key_len)
{
    char *key;

    while (str[*key_len] != '\0' && str[*key_len] != '=')
        (*key_len)++;
    key = malloc(sizeof(char) * (*key_len + 1));
    if (!key)
        return NULL;
    return my_strncpy(key, str, *key_len);
}

char *malloc_env_value(char *str, int key_len)
{
    char *value = malloc(sizeof(char) * (my_strlen(str + key_len) + 1));

    if (!value)
        return NULL;
    return my_strcpy(value, str + key_len);
}

myenv_t *create_env_node(char *line)
{
    myenv_t *node = malloc(sizeof(myenv_t));
    int key_len = 0;

    if (!node)
        return NULL;
    node->key = malloc_env_key(line, &key_len);
    node->value = malloc_env_value(line, key_len + 1);
    node->full_line = my_strdup(line);
    node->next = NULL;
    if (!node->key || !node->value || !node->full_line)
        return NULL;
    return node;
}

int push_in_myenv(myenv_t **head, char *line)
{
    myenv_t *current = (*head);

    if (!current) {
        (*head) = create_env_node(line);
        if (!(*head))
            return 84;
    }
    else {
        while (current->next != NULL)
            current = current->next;
        current->next = create_env_node(line);
        if (!current->next)
            return 84;
    }
    return 0;
}