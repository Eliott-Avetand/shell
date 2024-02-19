/*
** EPITECH PROJECT, 2020
** my_swap.c
** File description:
** Swap content of two int given as parameter using pointers
** {Epi-Lib}, created by Grégoire Biendiné.
** PLEASE DON'T COPY THIS FILE.
*/

void my_swap(int *a, int *b)
{
    int temp = *a;

    *a = *b;
    *b = temp;
}
