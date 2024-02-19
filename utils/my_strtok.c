/*
** EPITECH PROJECT, 2020
** my_strtok.c
** File description:
** Split string in other strings at given delimiters
*/

#include "shell.h"

int is_double_delim(char *arg, int i)
{
    if ((is_delim(arg[i]) == 1 || arg[i] == '&') &&
    arg[i] == arg[i + 1])
        return 1;
    return 0;
}

int get_nb_token(char *arg)
{
    int co = 0;
    int in_quote = 0;

    if (!arg)
        return -1;
    for (int i = 0; arg[i] != '\0'; i++) {
        if (arg[i] == '\'' || arg[i] == '"')
            in_quote = (in_quote == 0) ? 1 : 0;
        if (in_quote == 0 && is_double_delim(arg, i)) {
            co++;
            i++;
        } else if (in_quote == 0 && (is_delim(arg[i]) || arg[i + 1] == '\0'))
            co++;
    }
    return co;
}

char **malloc_tokens(char *arg)
{
    char **token = malloc(sizeof(char *) * (get_nb_token(arg) + 1));
    int tok_idx = 0;
    int bornes = 0;
    int in_quote = 0;

    if (!token)
        return NULL;
    for (int i = 0; arg[i] != '\0'; i++) {
        if (arg[i] == '\'' || arg[i] == '"')
            in_quote = (in_quote == 0) ? 1 : 0;
        if (in_quote == 0 && (arg[i + 1] == '\0' ||
        is_delim(arg[i]) || is_double_delim(arg, i))) {
            token[tok_idx] = malloc(sizeof(char) * ((i - bornes)) + 2);
            tok_idx++;
            i += (is_double_delim(arg, i)) ? 1 : 0;
            bornes = i;
        }
    }
    return token;
}

void fill_tokens(char ***tokens, char *str, int *tok_idx, int *char_idx)
{
    int in_quote = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\'' || str[i] == '"') {
            in_quote = (in_quote == 0) ? 1 : 0;
            continue;
        }
        if ((!is_delim(str[i]) && !is_double_delim(str, i)) || in_quote == 1)
            (*tokens)[(*tok_idx)][(*char_idx)++] = str[i];
        else {
            (*tokens)[(*tok_idx)++][*char_idx] = '\0';
            (*char_idx) = 0;
            i += (is_double_delim(str, i)) ? 1 : 0;
        }
    }
}

char **my_strtok(char *str)
{
    char **tokens = malloc_tokens(str);
    int tok_idx = 0;
    int char_idx = 0;

    if (!tokens || (str && str[0] == '\0'))
        return NULL;
    fill_tokens(&tokens, str, &tok_idx, &char_idx);
    tokens[tok_idx++][char_idx] = '\0';
    tokens[tok_idx] = NULL;
    return tokens;
}