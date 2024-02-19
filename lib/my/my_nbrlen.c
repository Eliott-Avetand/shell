/*
** EPITECH PROJECT, 2020
** my_nbrlen.c
** File description:
** Get length of a number
*/

int my_nbrlen(int nb)
{
    int len = 0;
    int save = nb;

    if (nb < 0) {
        len++;
        nb *= -1;
    }
    while (nb > 0) {
        len++;
        nb /= 10;
    }
    return (save == 0) ? 1 : len;
}