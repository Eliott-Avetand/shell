/*
** EPITECH PROJECT, 2020
** my_str_isalpha.c
** File description:
** Check if string contain alpha char
** {Epi-Lib}, created by Grégoire Biendiné.
** PLEASE DON'T COPY THIS FILE.
*/

int my_str_isalpha(char const *str)
{
    for (int i = 0; str[i]; i++) {
        if (!((str[i] >= 'a' && str[i] <= 'z') ||
            (str[i] >= 'A' && str[i] <= 'Z')))
            return 0;
    }
    return 1;
}
