/*
** EPITECH PROJECT, 2020
** my_strncpy.c
** File description:
** Copy n char from string to another
** {Epi-Lib}, created by Grégoire Biendiné.
** PLEASE DON'T COPY THIS FILE.
*/

char *my_strncpy(char *dest, char const *src, int n)
{
    int j = 0;

    for (int i = 0; src[i] != '\0' && i < n; i++, j++)
        dest[j] = src[i];
    dest[j] = '\0';
    return dest;
}
