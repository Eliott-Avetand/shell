/*
** EPITECH PROJECT, 2020
** bt_alias.c
** File description:
** Handle alias builtin
*/

#include "shell.h"

char *replace_alias_in_string(char *str, char *to_find, char *replace)
{
    char *dest = malloc(sizeof(char) * (strlen(str) -
    strlen(to_find) + strlen(replace) + 1));

    if (!dest)
        return NULL;
    dest[0] = '\0';
    if (strncmp(str, to_find, strlen(to_find)) == 0) {
        strcat(dest, replace);
        return strcat(dest, str + strlen(to_find));
    }
    free(dest);
    return NULL;
}

void check_aliases(data_t *data, char *line)
{
    alias_t *current = data->lists->alias;
    char *new_str;

    while (current != NULL) {
        new_str = replace_alias_in_string(line, current->key, current->value);
        if (new_str) {
            free(data->clean_input);
            data->clean_input = new_str;
            return;
        }
        current = current->next;
    }
}

void list_alias(alias_t *head)
{
    alias_t *current = head;

    while (current != NULL) {
        printf("%s\t%s\n", current->key, current->value);
        current = current->next;
    }
}

void bt_unalias(data_t *data, char **args)
{
    int ac = word_array_len(args);

    if (ac == 1)
        return print_error("unalias", "Too few arguments.\n", 1);
    if (strcmp(args[1], "-a") == 0) {
        free_alias_list(data->lists->alias);
        data->lists->alias = NULL;
        return;
    }
    for (int i = 1; args[i] != NULL; i++) {
        remove_alias_from_key(&data->lists->alias, args[i]);
    }
}

void bt_alias(data_t *data, char **args)
{
    int ac = word_array_len(args);
    char *value;

    if (ac == 1 || (ac == 2 && strcmp(args[1], "-p") == 0))
        list_alias(data->lists->alias);
    else if (ac > 2) {
        value = word_array_to_string(args + 2);
        if (!value)
            return print_error("alias", INTERNAL_ERR, 1);
        modify_or_push_alias(data, args[1], value);
        free(value);
    }
    data->exit = 0;
}