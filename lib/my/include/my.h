/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header for our personal lib
** {Epi-Lib}, created by Grégoire Biendiné.
** PLEASE DON'T COPY THIS FILE.
*/

#ifndef MY_H
#define MY_H

#include <stdlib.h>
#include <stdarg.h>

#define MY_PRINTF_FLAGS "csd"

// string :
char *my_strcat(char *dest, char const *src);
char *my_strncat(char *dest, char const *src, int nb);
int my_strncmp(char const *s1, char const *s2, int n);
int my_strcmp(char const *a, char const *b);
char *my_strcpy(char *dest, char const *src);
char *my_strncpy(char *dest, char const *src, int n);
char *my_revstr(char *str);
char *my_strstr(char *str, char const *to_find);
char *my_strdup(char const *str);
int my_strlen(char const *str);
char *my_strupcase(char *str);
int my_getnbr(char const *str);
char **str_to_word_array(char *str, char delim);
int my_printf(const char *format, ...);

// math :
int my_pow(int nb, int p);
int my_sqrt(int nb);
int my_nbrlen(int nb);

// display :
void my_putchar(char c);
void my_putstr(char const *str);
int my_put_nbr(int nb);
void my_put_float(float nb, int prec);

// other :
int my_str_isalpha(char const *str);
char *my_strlowcase(char *str);
void my_swap(int *a, int *b);

// my_printf :
void disp_normal_char(char c, int *len);
void disp_char(va_list *list, int *len);
void disp_string(va_list *list, int *len);
void disp_int(va_list *list, int *len);

#endif
