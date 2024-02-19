/*
** EPITECH PROJECT, 2020
** my_strstr.c
** File description:
** Search string in another
** {Epi-Lib}, created by Grégoire Biendiné.
** PLEASE DON'T COPY THIS FILE.
*/

#include <stdio.h>

void my_putchar(char c);

int get_str_length(char *str)
{
    int i = 0;

    for (i; str[i] != '\0'; i++);
    return i;
}

int get_tf_length(char const *str)
{
    int i = 0;

    for (i; str[i] != '\0'; i++);
    return i;
}

char *my_strstr(char *str, char const *to_find)
{
    int str_length = get_str_length(str);
    int tf_length = get_tf_length(to_find);
    int bornes[2] = {0, tf_length};

    while (bornes[1] <= str_length) {
        for (int i = bornes[0]; i < bornes[1]; i++) {
            if (str[bornes[0]] == to_find[0]) {
                my_putchar(str[i]);
            }
        }
        bornes[0]++;
        bornes[1]++;
        my_putchar('\n');
    }
    return str;
}
