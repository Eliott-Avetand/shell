/*
** EPITECH PROJECT, 2020
** my_put_nbr.c
** File description:
** Display given number
** {Epi-Lib}, created by Grégoire Biendiné.
** PLEASE DON'T COPY THIS FILE.
*/

void my_putchar(char c);

int my_put_nbr(int nb)
{
    int modulo = 0;
    int save_nb = 0;

    if (nb < 0) {
        my_putchar('-');
        nb *= -1;
    }
    if (nb >= 10) {
        modulo = (nb % 10);
        save_nb = (nb - modulo) / 10;
        my_put_nbr(save_nb);
        my_putchar(48 + modulo);
    } else
        my_putchar(48 + (nb % 10));
    return 0;
}
