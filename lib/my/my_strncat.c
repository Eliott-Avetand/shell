/*
** EPITECH PROJECT, 2020
** my_strncat.c
** File description:
** Concat two string for n char
** {Epi-Lib}, created by Grégoire Biendiné.
** PLEASE DON'T COPY THIS FILE.
*/

char *my_strncat(char *dest, char const *src, int nb)
{
    int i = 0;
    int j = 0;
    int co = 0;

    for (i; dest[i] != '\0'; i++);
    for (j = i; src[co] != '\0'; j++) {
        if (co < nb) {
            dest[j] = src[co];
        } else {
            dest[j] = '\0';
        }
        co++;
    }
    dest[j] = '\0';
    return dest;
}
