/*
** EPITECH PROJECT, 2020
** my_strlowcase.c
** File description:
** Low case all char of string
** {Epi-Lib}, created by Grégoire Biendiné.
** PLEASE DON'T COPY THIS FILE.
*/

char *my_strlowcase(char *str)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
    }
    return str;
}
