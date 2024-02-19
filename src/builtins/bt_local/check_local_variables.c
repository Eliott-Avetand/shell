/*
** EPITECH PROJECT, 2020
** check_local_variables.c
** File description:
** Check local variables
*/

#include "shell.h"

char *delete_spaces(char *str, int len)
{
    char *ret = NULL;
    int x = 0;

    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == ' ' && str[i + 1] == '=' && str[i + 2] == ' ')
            len -= 2;
    ret = malloc(sizeof(char) * (len + 1));
    ret[len] = '\0';
    for (int j = 0; str[j] != '\0'; j++) {
        if (str[j] == ' ' && str[j + 1] == '=' && str[j + 2] == ' ');
        else if (j > 2 && str[j] == ' ' && str[j - 1] == '='
            && str[j - 2] == ' ');
        else {
            ret[x] = str[j];
            x++;
        }
    }
    return ret;
}

void free_local_list(mylocal_t *head)
{
    mylocal_t *current;

    while (head != NULL) {
        current = head;
        head = head->next;
        free_local_node(current);
    }
}

int local_str_isvalid(char *str)
{
    if (!((str[0] >= 65 && str[0] <= 90) ||
    (str[0] >= 97 && str[0] <= 122) || str[0] == '_')) {
        print_error("set", SETENV_LTRFIRST, 1);
        return -1;
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if (!((str[i] >= 65 && str[i] <= 90) || str[i] == '_' ||
        (str[i] >= 97 && str[i] <= 122) || (str[i] >= 48 && str[i] <= 57))) {
            if (str[i] != '=') {
                print_error("set", SETENV_NONALPHA, 1);
                return -1;
            }
        }
    }
    return 0;
}

char *get_local_value(char *line, int x, char *value)
{
    int y = 0;

    if (line[x] == '\0' || (line[x] == '=' && line[x + 1] == '\0')) {
        value = NULL;
    } else {
        value = malloc(sizeof(char) * (my_strlen(line) - x));
        value[(my_strlen(line) - x - 1)] = '\0';
        for (int k = x + 1; line[k] != '\0'; k++) {
            value[y] = line[k];
            y++;
        }
    }
    return (value);
}