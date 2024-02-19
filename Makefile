##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

SRC		    =	main.c											\
				src/create_data_struct.c 						\
				src/bin_research.c								\
				src/cleanup.c									\
				src/list/myenv_handler.c 						\
				src/list/mypath_handler.c 						\
				src/list/command_handler.c 						\
				src/list/alias_handler.c 						\
				src/list/dlr_storage_handler.c 					\
				src/list/add_commands_to_list.c 				\
				src/list/modify_myenv.c 						\
				src/list/free_list.c 							\
				src/user_input/process_user_input.c				\
				src/user_input/clean_user_input.c				\
				src/user_input/clean_delim.c					\
				src/user_input/backticks/check_backticks.c		\
				src/user_input/backticks/parse_subcommand.c		\
				src/user_input/backticks/replace_in_backticks.c	\
				src/user_input/backticks/execute_backticks.c	\
				src/user_input/backticks/backticks_file.c	\
				src/execution/my_exec.c							\
				src/execution/my_exec_pipe.c					\
				src/execution/my_redirection.c					\
				src/builtins/bt_history/events/events_handler.c	\
				src/builtins/bt_history/events/parse_events.c	\
				src/builtins/bt_history/events/events_utils.c	\
				src/builtins/bt_history/events/events_checker.c	\
				src/builtins/bt_history/bt_history.c			\
				src/builtins/bt_history/history_error.c			\
				src/builtins/bt_history/history_handler.c		\
				src/builtins/bt_history/history_list.c			\
				src/builtins/bt_alias/bt_alias.c				\
				src/builtins/bt_alias/modify_alias_list.c		\
				src/builtins/bt_local/bt_local.c 				\
				src/builtins/bt_local/add_local_variables.c		\
				src/builtins/bt_local/check_local_variables.c	\
				src/builtins/bt_local/modify_local_nodes.c		\
				src/builtins/bt_local/bt_echo.c					\
				src/builtins/builtins.c							\
				src/builtins/bt_cd.c							\
				src/builtins/bt_setenv.c						\
				src/show_prompt/print_prompt.c					\
				src/show_prompt/get_dir_name.c					\
				utils/word_array_utils.c						\
				utils/my_strtok.c								\
				utils/my_getline.c								\
				utils/myenv_to_word_array.c 					\
				utils/str_utils.c								\
				utils/print_error.c								\
				utils/nbr_of_digits.c							\

OBJ		    =	$(SRC:.c=.o)

NAME	    =	42sh

CFLAGS		+=	-W -Wall -Wextra -I./include

INCLUDES 	=	-L./lib -lmy

all:	$(OBJ)
	@$(MAKE) -C ./lib/my/
	@gcc -o $(NAME) $(OBJ) $(CFLAGS) $(INCLUDES)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

debug: fclean
	@$(MAKE) -C ./lib/my/
	@gcc -o $(NAME) $(SRC) $(CFLAGS) $(INCLUDES) -g

valgrind: debug
	valgrind --leak-check=full --show-leak-kinds=all ./42sh

re: fclean all

.PHONY: all clean fclean re debug valgrind
