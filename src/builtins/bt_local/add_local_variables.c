/*
** EPITECH PROJECT, 2020
** add_local_variables.c
** File description:
** Add local variables
*/

#include "shell.h"

char *malloc_local_key(char *str, int *key_len)
{
    char *key;

    while (str[*key_len] != '\0' && str[*key_len] != '\t')
        (*key_len)++;
    key = malloc(sizeof(char) * (*key_len + 1));
    if (!key)
        return NULL;
    return my_strncpy(key, str, *key_len);
}

char *malloc_local_value(char *str, int key_len)
{
    char *value = malloc(sizeof(char) * (my_strlen(str + key_len) + 1));

    if (!value)
        return NULL;
    return my_strcpy(value, str + key_len);
}

mylocal_t *create_local_node(char *line)
{
    mylocal_t *node = malloc(sizeof(mylocal_t));
    int key_len = 0;

    if (!node)
        return NULL;
    node->key = malloc_local_key(line, &key_len);
    node->value = malloc_local_value(line, key_len + 1);
    node->full_line = my_strdup(line);
    node->next = NULL;
    if (!node->key || !node->value || !node->full_line)
        return NULL;
    return node;
}

int push_in_mylocal(mylocal_t **head, char *line)
{
    mylocal_t *current = (*head);

    if (!current) {
        (*head) = create_local_node(line);
        if (!(*head))
            return 84;
    }
    else {
        while (current->next != NULL)
            current = current->next;
        current->next = create_local_node(line);
        if (!current->next)
            return 84;
    }
    return 0;
}

void add_key_to_mylocal(data_t *data, char *key, char *value)
{
    char *full_line;

    if (get_value_by_key_local(data->lists->local, key) != NULL)
        modify_value_from_key_local(data->lists->local, key, value);
    else {
        full_line = concat_two_string(key, value, "\t");
        if (!full_line)
            return print_error("set", INTERNAL_ERR, 1);
        push_in_mylocal(&data->lists->local, full_line);
        free(full_line);
        data->exit = 0;
    }
}