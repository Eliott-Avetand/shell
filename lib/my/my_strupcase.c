/*
** EPITECH PROJECT, 2020
** my_strupcase.c
** File description:
** Upcase all char of a string
** {Epi-Lib}, created by Grégoire Biendiné.
** PLEASE DON'T COPY THIS FILE.
*/

char *my_strupcase(char *str)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 32;
    }
    return str;
}
