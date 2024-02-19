/*
** EPITECH PROJECT, 2020
** bt_local.c
** File description:
** Handle local variables
*/

#include "shell.h"

int bt_set2(data_t *data, char *variable, char *value)
{
    char *new_value = (value != NULL) ? value : "\0";

    if (local_str_isvalid(variable) != 0) {
        free(variable);
        free(value);
        data->exit = -1;
        return -1;
    }
    add_key_to_mylocal(data, variable, new_value);
    data->exit = 0;
    return (0);
}

void set_all_locals(data_t *data, char *tmp)
{
    char *str = delete_spaces(tmp, my_strlen(tmp));
    char **tab = str_to_word_array(str, ' ');
    char *variable = NULL;
    char *value = NULL;
    int x = 0;

    free(str);
    for (int i = 0; tab[i] != NULL; i++) {
        for (int j = 0; tab[i][j] != '=' && tab[i][j] != '\0'; j++)
            x++;
        variable = malloc(sizeof(char) * (x + 1));
        variable = my_strncpy(variable, tab[i], x);
        value = get_local_value(tab[i], x, value);
        if (bt_set2(data, variable, value) == -1)
            break;
        free(variable);
        free(value);
        x = 0;
    }
    free_tab(tab);
}

void print_local(data_t *data, UNUSED char **args)
{
    mylocal_t *current = data->lists->local;

    while (current != NULL) {
        printf("%s\n", current->full_line);
        current = current->next;
    }
}

void bt_set(data_t *data, char **args)
{
    int len = 0;
    char *str = NULL;
    int x = 0;

    if (word_array_len(args) == 1)
        return print_local(data, args);
    for (int i = 1; args[i] != NULL; i++)
        len += my_strlen(args[i]) + 1;
    str = malloc(sizeof(char) * len + 1);
    str[len] = '\0';
    for (int i = 1; args[i] != NULL; i++) {
        for (int j = 0; args[i][j] != '\0'; j++) {
            str[x] = args[i][j];
            x++;
        }
        str[x] = ' ';
        x++;
    }
    set_all_locals(data, str);
    free(str);
}

void bt_unset(data_t *data, char **args)
{
    int ac = word_array_len(args);

    if (ac < 2)
        return print_error("unset", "Too few arguments.\n", 1);
    for (int i = 1; args[i] != NULL; i++)
        remove_node_from_key_local(&data->lists->local, args[i]);
    data->exit = 0;
}