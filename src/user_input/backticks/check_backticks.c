/*
** EPITECH PROJECT, 2020
** clean_delim.c
** File description:
** Clean delimitor from user input
*/

#include "shell.h"

int count_backticks(char *line)
{
    int nbr = 0;

    for (int i = 0; line[i]; i++) {
        if (line[i] == '`')
            nbr++;
    }
    return nbr;
}

void get_backticks_command(char **line, char *result, char *new_command,
char *subcommand)
{
    new_command = replace_in_backticks((*line), result);
    free((*line));
    (*line) = strdup(new_command);
    free(new_command);
    free(result);
    free(subcommand);
}

int check_backticks(data_t *data, char **line)
{
    int nbr_backticks = count_backticks((*line));
    char *subcommand = NULL;
    char *new_command = NULL;
    char *result = NULL;

    if (nbr_backticks == 0)
        return 0;
    else if ((nbr_backticks % 2) != 0) {
        fprintf(stderr, "Unmatched '`'.\n");
        return -1;
    }
    subcommand = parse_subcommand((*line));
    result = exec_bacticks(data, subcommand);
    if (!result)
        return -1;
    get_backticks_command(line, result, new_command, subcommand);
    return 1;
}