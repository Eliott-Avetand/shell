##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile for lib
##

SRC		=	my_pow.c					\
			my_sqrt.c					\
			my_getnbr.c					\
			my_putchar.c				\
			my_put_float.c				\
			my_put_nbr.c				\
			my_putstr.c					\
			my_revstr.c					\
			my_strcat.c					\
			my_strcmp.c					\
			my_strcpy.c					\
			my_str_isalpha.c			\
			my_strlen.c					\
			my_nbrlen.c					\
			my_strlowcase.c				\
			my_strncat.c				\
			my_strncmp.c				\
			my_strncpy.c				\
			my_strstr.c					\
			my_strupcase.c				\
			my_swap.c					\
			my_strdup.c					\
			str_to_word_array.c			\
			my_itoa.c					\
			my_printf.c					\
			my_printf_src/my_printf_disp.c

OBJ		=	$(SRC:.c=.o)

all:	$(OBJ)
	@ar rc libmy.a $(OBJ)
	@cp ./libmy.a ../
	@cp include/my.h ../../include/

clean:
	@rm -f $(OBJ)
	@rm -f libmy.a
	@rm -f ../libmy.a

.PHONY:	all clean
