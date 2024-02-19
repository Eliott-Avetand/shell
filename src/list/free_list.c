/*
** EPITECH PROJECT, 2020
** free_list.c
** File description:
** Free all lists
*/

#include "shell.h"

void free_env_node(myenv_t *node)
{
    free(node->key);
    if (node->value != NULL)
        free(node->value);
    free(node->full_line);
    free(node);
}

void free_env_list(myenv_t *head)
{
    myenv_t *current;

    while (head != NULL) {
        current = head;
        head = head->next;
        free_env_node(current);
    }
}

void free_path_list(mypath_t *head)
{
    mypath_t *current;

    while (head != NULL) {
        current = head;
        head = head->next;
        free(current->folder);
        free(current);
    }
}

void free_dlr_list(dlr_storage_t *head)
{
    dlr_storage_t *current;

    while (head != NULL) {
        current = head;
        head = head->next;
        free(current->line);
        free(current);
    }
}

void free_command_list(command_t *head)
{
    command_t *current;

    if (!head)
        return;
    while (head != NULL) {
        current = head;
        head = head->next;
        free_tab(current->args);
        free(current->bin_path);
        free(current);
    }
}