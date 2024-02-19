/*
** EPITECH PROJECT, 2020
** dlr_storage_handler.c
** File description:
** Handle double left redir input storage list
*/

#include "shell.h"

dlr_storage_t *create_dlr_node(char *str)
{
    dlr_storage_t *node = malloc(sizeof(dlr_storage_t));

    if (!node)
        return NULL;
    node->line = my_strdup(str);
    node->next = NULL;
    if (!node->line)
        return NULL;
    return node;
}

int push_dlr_node(dlr_storage_t **head, char *line)
{
    dlr_storage_t *current = (*head);

    if (!current) {
        (*head) = create_dlr_node(line);
        if (!(*head))
            return -1;
    } else {
        while (current->next != NULL)
            current = current->next;
        current->next = create_dlr_node(line);
        if (!current->next)
            return -1;
    }
    return 0;
}

char *concat_dlr_storage(dlr_storage_t *head)
{
    dlr_storage_t *current = head;
    char *full_line;
    int len = 0;

    if (!head)
        return NULL;
    while (current != NULL) {
        len += strlen(current->line);
        current = current->next;
    }
    full_line = malloc(sizeof(char) * (len + 1));
    if (!full_line)
        return NULL;
    full_line[0] = '\0';
    current = head;
    while (current != NULL) {
        strcat(full_line, current->line);
        current = current->next;
    }
    return full_line;
}

int compare_end_str(char *input, char *end_str)
{
    int len = 0;

    for (int i = 0; input[i] != '\n'; i++) {
        len++;
        if (input[i] != end_str[i])
            return 1;
    }
    if ((int)strlen(end_str) != len)
        return 1;
    return 0;
}

char *get_dlr_input(char *end_str)
{
    dlr_storage_t *head = NULL;
    char *input = NULL;
    char *full_line;

    my_putstr("? ");
    if (my_getline(&input, 0) == NULL)
        return NULL;
    while (compare_end_str(input, end_str) != 0) {
        push_dlr_node(&head, input);
        free(input);
        my_putstr("? ");
        if (my_getline(&input, 0) == NULL)
            break;
    }
    free(input);
    full_line = concat_dlr_storage(head);
    free_dlr_list(head);
    return full_line;
}