/*
** EPITECH PROJECT, 2020
** add_commands_to_list.c
** File description:
** Add all commands to command list
*/

#include "shell.h"

delimiter get_delim(char *str, int idx)
{
    if (str[idx] == '|' && str[idx + 1] != '|')
        return PIPE;
    if (str[idx] == ';')
        return SEMICOLON;
    if (str[idx] == '>' && str[idx + 1] != '>')
        return S_RIGHT;
    if (str[idx] == '<' && str[idx + 1] != '<')
        return S_LEFT;
    if (str[idx] == '>' && str[idx + 1] == '>')
        return D_RIGHT;
    if (str[idx] == '<' && str[idx + 1] == '<')
        return D_LEFT;
    if (str[idx] == '&' && str[idx + 1] == '&')
        return AND;
    if (str[idx] == '|' && str[idx + 1] == '|')
        return OR;
    return VOID;
}

int *create_delim_list(char **cmds, char *str)
{
    int len = word_array_len(cmds);
    int *list = malloc(sizeof(int) * (len + 2));
    int bornes = 0;
    int co = 0;

    if (!list)
        return NULL;
    list[co++] = VOID;
    for (int i = 0; str[i] != '\0'; i++) {
        if ((is_delim(str[i]) || is_double_delim(str, i)) &&
        i - bornes >= my_strlen(cmds[co - 1])) {
            list[co++] = get_delim(str, i);
            i += (is_double_delim(str, i)) ? 1 : 0;
        }
    }
    list[co] = VOID;
    return list;
}

int add_commands_to_list(data_t *data, char *input)
{
    char **cmds = my_strtok(input);
    int *delim_list;

    if (!cmds)
        return 1;
    delim_list = create_delim_list(cmds, input);
    if (!delim_list)
        return 1;
    for (int i = 0; cmds[i] != NULL; i++) {
        if (push_command(data, cmds[i], delim_list[i + 1], delim_list[i]) != 0)
            return 1;
    }
    free(delim_list);
    free_tab(cmds);
    return 0;
}