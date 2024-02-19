/*
** EPITECH PROJECT, 2020
** main.c
** File description:
** Main file for shell
*/

#include "shell.h"

int prompt(data_t *data)
{
    int exit_code = 0;

    print_prompt(data);
    while (data->is_exited == 0 && my_getline(&data->input, 1) != NULL) {
        if (data->input[0] != '\0')
            process_user_input(data);
        free(data->input);
        if (data->is_exited == 0)
            print_prompt(data);
    }
    exit_code = data->exit;
    free_data(data);
    my_putstr("exit\n");
    return exit_code;
}

int main(int ac, UNUSED char **av, char **envp)
{
    data_t *data = NULL;
    int exit_code = 0;

    if (ac != 1)
        return 84;
    data = create_data_struct(envp);
    if (!data)
        return 84;
    exit_code = prompt(data);
    return (exit_code == 139 || exit_code == 136) ? 0 : exit_code;
}
