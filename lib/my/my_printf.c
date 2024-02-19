/*
** EPITECH PROJECT, 2020
** my_printf.c
** File description:
** my_printf function
*/

#include "include/my.h"

int is_flag(char c)
{
    for (int i = 0; MY_PRINTF_FLAGS[i]; i++) {
        if (MY_PRINTF_FLAGS[i] == c)
            return 1;
    }
    return 0;
}

int compute_flag(char c, int *len, va_list *list)
{
    if (c == '%')
        disp_normal_char('%', len);
    else if (is_flag(c) == 1) {
        if (c == 'c')
            disp_char(list, len);
        else if (c == 's')
            disp_string(list, len);
        else
            disp_int(list, len);
    } else
        return -1;
}

int my_printf(const char *format, ...)
{
    va_list list;
    int length = 0;

    va_start(list, format);
    for (int i = 0; format[i]; i++) {
        if (format[i] != '%')
            disp_normal_char(format[i], &length);
        else if (compute_flag(format[++i], &length, &list) == -1)
            return -1;
    }
    va_end(list);
    return length;
}