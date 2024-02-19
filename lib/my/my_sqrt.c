/*
** EPITECH PROJECT, 2020
** my_compute_square_root.c
** File description:
** Square root of number
** {Epi-Lib}, created by Grégoire Biendiné.
** PLEASE DON'T COPY THIS FILE.
*/

int my_sqrt(int nb)
{
    int res = 0;

    while ((res * res) != nb) {
        res++;
        if (res > nb)
            return 0;
    }
    return res;
}
