/*
** EPITECH PROJECT, 2020
** nbr_of_digits.c
** File description:
** Count the number of digits.
*/

#include "shell.h"

int count_digits(int nbr)
{
    int res = nbr;
    int digits = 0;

    while (res != 0) {
        res = res / 10;
        digits++;
    }
    return digits;
}