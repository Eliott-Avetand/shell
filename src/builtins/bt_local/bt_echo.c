/*
** EPITECH PROJECT, 2020
** bt_echo.c
** File description:
** Handle echo $ builtin
*/

#include "shell.h"

int is_echo_builtin(char **args)
{
    char echo[4] = "echo";

    for (int j = 0; j < 4; j++)
        if (args[0][j] != echo[j])
            return 0;
    if (args[1] == NULL || args[1][0] != '$' || args[1][1] == '\0')
        return 0;
    return 1;
}

void print_value(data_t *data, char *str)
{
    char *local_value = get_value_by_key_local(data->lists->local, str);
    char *env_value = get_value_by_key(data->lists->env, str);

    if (local_value != NULL)
        my_putstr(local_value);
    else if (env_value != NULL)
        my_putstr(env_value);
    else
        print_error(str, "Undefined variable.", 1);
}

void bt_echo(data_t *data, char **args)
{
    char *str = malloc(sizeof(char) * my_strlen(args[1]));

    for (int i = 1; args[1][i] != '\0'; i++)
        str[i - 1] = args[1][i];
    str[my_strlen(args[1]) - 1] = '\0';
    if (args[1] != NULL && args[1][1] == '?') {
        my_printf("%d", data->exit);
        data->exit = 0;
    } else {
        data->exit = 0;
        print_value(data, str);
    }
    my_putchar('\n');
    free(str);
}