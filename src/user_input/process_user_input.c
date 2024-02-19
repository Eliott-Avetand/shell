/*
** EPITECH PROJECT, 2020
** process_user_input.c
** File description:
** Clean user input and iterate through commands
*/

#include "shell.h"

void choose_command_type(data_t *data, command_t *current)
{
    if (((current->next_delim == SEMICOLON || current->next_delim == VOID ||
    current->next_delim == AND || current->next_delim == OR) &&
    current->prev_delim != PIPE) || get_cmd_count(data->lists->commands) == 1)
        return my_exec(data, current);
    if (current->next_delim == PIPE || current->prev_delim == PIPE)
        my_exec_pipe(data, current);
    if (current->next_delim == S_RIGHT && current->next)
        right_redir(data, current, OPEN_SR_FLAG);
    if (current->next_delim == D_RIGHT && current->next)
        right_redir(data, current, OPEN_DR_FLAG);
    if (current->next_delim == S_LEFT && current->next)
        left_redir(data, current);
    if (current->next_delim == D_LEFT && current->next)
        double_left_redir(data, current);
}

void avoid_other_commands(command_t **current)
{
    while ((*current)->next_delim == PIPE && (*current)->next_delim != VOID)
        (*current) = (*current)->next;
}

void iterate_through_commands(data_t *data)
{
    command_t *current = data->lists->commands;

    while (current != NULL) {
        if (current->type == NOT_FOUND)
            return print_error(current->args[0], CMD_NOTFOUND, 1);
        if ((current->prev_delim == AND && data->exit != 0) ||
        (current->prev_delim == OR && data->exit == 0))
            avoid_other_commands(&current);
        else
            choose_command_type(data, current);
        if (current->next_delim >= S_RIGHT &&
        current->next_delim <= D_LEFT && current->next)
            current = current->next;
        current = current->next;
    }
}

void process_user_input(data_t *data)
{
    data->clean_input = clean_user_input(data->input);
    if (!data->clean_input)
        return print_error(NULL, NULL, 1);
    if (events_handler(data) == -1 || check_backticks(data,
    &data->clean_input) == -1)
        return;
    check_aliases(data, data->clean_input);
    if (add_commands_to_list(data, data->clean_input) != 0) {
        free(data->clean_input);
        return print_error(NULL, NULL, 0);
    }
    check_history_list(&data->lists->history, data->clean_input);
    push_in_history(&data->lists->history, data->clean_input);
    iterate_through_commands(data);
    free(data->clean_input);
    free_command_list(data->lists->commands);
    data->lists->commands = NULL;
}