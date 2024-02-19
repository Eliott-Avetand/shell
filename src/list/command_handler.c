/*
** EPITECH PROJECT, 2020
** command_handler.c
** File description:
** Handle command linked list creation and modification
*/

#include "shell.h"

int get_cmd_count(command_t *head)
{
    command_t *current = head;
    int co = 0;

    while (current != NULL) {
        co++;
        current = current->next;
    }
    return co;
}

command_t *create_cmd_node(data_t *data, char *line,
delimiter next_delim, delimiter prev_delim)
{
    command_t *node = malloc(sizeof(command_t));

    if (!node)
        return NULL;
    node->args = str_to_word_array(line, ' ');
    node->bin_path = analyse_first_arg(data, node);
    node->next_delim = next_delim;
    node->prev_delim = prev_delim;
    node->next = NULL;
    node->prev = NULL;
    if (!node->args)
        return NULL;
    return node;
}

int push_command(data_t *data, char *line, delimiter next, delimiter prev)
{
    command_t *current = data->lists->commands;

    if (!current) {
        data->lists->commands = create_cmd_node(data, line, next, prev);
        if (!data->lists->commands)
            return 1;
    }
    else {
        while (current->next != NULL)
            current = current->next;
        current->next = create_cmd_node(data, line, next, prev);
        current->next->prev = current;
        if (!current->next)
            return 1;
    }
    return 0;
}