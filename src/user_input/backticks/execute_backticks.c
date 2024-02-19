/*
** EPITECH PROJECT, 2020
** clean_delim.c
** File description:
** Clean delimitor from user input
*/

#include "shell.h"

int begin_backticks_command(data_t *data, char *clear_line)
{
    if (add_commands_to_list(data, clear_line) != 0) {
        free(clear_line);
        return -1;
    }
    free(clear_line);
    iterate_through_commands(data);
    free_command_list(data->lists->commands);
    data->lists->commands = NULL;
    return 0;
}

int execute_backticks_command(data_t *data, char *clear_line, pid_t pid,
int fd)
{
    pid = fork();
    if (pid < 0)
        return -1;
    else if (pid == 0) {
        dup2(fd, STDOUT_FILENO);
        if (begin_backticks_command(data, clear_line) != 0) {
            close(fd);
            my_exit(data);
        }
        close(fd);
        my_exit(data);
    }
    wait_child(pid);
    return 0;
}

char *exec_bacticks(data_t *data, char *clear_line)
{
    char *buffer = NULL;
    int fd = open("backticks_tmp", OPEN_SR_FLAG, OPEN_R_MODE);
    pid_t pid = 0;

    if (fd == -1)
        return NULL;
    if (execute_backticks_command(data, clear_line, pid, fd) == -1)
        return NULL;
    close(fd);
    buffer = read_file("backticks_tmp");
    if (!buffer)
        return NULL;
    return buffer;
}