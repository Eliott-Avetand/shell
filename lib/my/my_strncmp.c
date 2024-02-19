/*
** EPITECH PROJECT, 2020
** my_strncmp.c
** File description:
** Compare two string for n char
** {Epi-Lib}, created by Grégoire Biendiné.
** PLEASE DON'T COPY THIS FILE.
*/

int my_strncmp(char const *s1, char const *s2, int n)
{
    for (int i = 0; (s1[i] != '\0' || s2[i] != '\0') && i < n; i++) {
        if (s1[i] < s2[i])
            return -1;
        else if (s1[i] > s2[i])
            return 1;
    }
    return 0;
}
