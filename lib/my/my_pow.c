/*
** EPITECH PROJECT, 2020
** my_pow.c
** File description:
** Returns number given to the power p
** {Epi-Lib}, created by Grégoire Biendiné.
** PLEASE DON'T COPY THIS FILE.
*/

int my_pow(int nb, int p)
{
    int res = 1;

    if (p == 0)
        return 1;
    if (p < 0)
        return 0;
    res = nb * my_pow(nb, p - 1);
    return res;
}