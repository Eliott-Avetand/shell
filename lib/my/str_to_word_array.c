/*
** EPITECH PROJECT, 2020
** str_to_word_array.c
** File description:
** String to array of strings
*/

#include "include/my.h"

char *parse_str(char *str, char delim)
{
    char *n_str = malloc(sizeof(char) * my_strlen(str) + 1);
    int ltr_check = 0;
    int co = 0;

    if (!str || !n_str || (str && str[0] == '\0'))
        return NULL;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\t')
            str[i] = delim;
        if (str[i] != delim) {
            n_str[co++] = str[i];
            ltr_check = 1;
        } else if (str[i + 1] != '\0' && str[i + 1] != delim &&
        str[i + 1] != '\t' && ltr_check == 1)
            n_str[co++] = str[i];
    }
    n_str[co] = '\0';
    return n_str;
}

int get_nb_word(char *arg, char delim)
{
    int co = 0;
    int in_quote = 0;

    if (!arg)
        return -1;
    for (int i = 0; arg[i] != '\0'; i++) {
        if (arg[i] == '\'' || arg[i] == '"')
            in_quote = (in_quote == 0) ? 1 : 0;
        if (in_quote == 0 && (arg[i] == delim || arg[i + 1] == '\0'))
            co++;
    }
    return co;
}

char **malloc_words(char *arg, char delim)
{
    char **words = malloc(sizeof(char *) * (get_nb_word(arg, delim) + 1));
    int word_idx = 0;
    int bornes = 0;
    int in_quote = 0;

    if (!words)
        return NULL;
    for (int i = 0; arg[i] != '\0'; i++) {
        if (arg[i] == '\'' || arg[i] == '"')
            in_quote = (in_quote == 0) ? 1 : 0;
        if (in_quote == 0 && (arg[i] == delim || arg[i + 1] == '\0')) {
            words[word_idx] = malloc(sizeof(char) * ((i - bornes)) + 2);
            word_idx++;
            bornes = i;
        }
    }
    for (int i = 0; i < get_nb_word(arg, delim); i++)
        if (!words[i])
            return NULL;
    return words;
}

int fill_word_array(char ***words, char *arg, int *word_idx, char delim)
{
    int char_idx = 0;
    int in_quote = 0;

    for (int i = 0; arg[i] != '\0'; i++) {
        if (arg[i] == '\'' || arg[i] == '"') {
            in_quote = (in_quote == 0) ? 1 : 0;
            continue;
        }
        if (arg[i] != delim || in_quote == 1)
            (*words)[*word_idx][char_idx++] = arg[i];
        else {
            (*words)[(*word_idx)++][char_idx] = '\0';
            char_idx = 0;
        }
    }
    return char_idx;
}

char **str_to_word_array(char *str, char delim)
{
    char *arg = parse_str(str, delim);
    char **words;
    int word_idx = 0;
    int char_idx = 0;

    if (!arg || (arg && arg[0] == '\0'))
        return NULL;
    words = malloc_words(arg, delim);
    if (!words) {
        free(arg);
        return NULL;
    }
    char_idx = fill_word_array(&words, arg, &word_idx, delim);
    words[word_idx++][char_idx] = '\0';
    words[word_idx] = NULL;
    free(arg);
    return words;
}