/*
** EPITECH PROJECT, 2020
** my_float_to_str.c
** File description:
** Convert float number to string
** {Epi-Lib}, created by Grégoire Biendiné.
** PLEASE DON'T COPY THIS FILE.
*/

int my_put_nbr(int nb);

void my_putchar(char c);

int my_compute_power_rec(int nb, int p);

void my_put_float(float nb, int prec)
{
    int int_part = (int)nb;
    int decim_part = (nb - int_part) * my_compute_power_rec(10, prec);

    my_put_nbr(int_part);
    my_putchar('.');
    my_put_nbr(decim_part);
    if (decim_part == 0)
        my_put_nbr(0);
}
