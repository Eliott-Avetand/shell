/*
** EPITECH PROJECT, 2020
** my_exec_pipe.c
** File description:
** Execute command if next or previous delimiter is a pipe
*/

#include "shell.h"

void redirect_to_file(command_t *head)
{
    int fd = open(head->next->args[0], (head->next_delim == S_RIGHT) ?
    OPEN_SR_FLAG : OPEN_DR_FLAG, OPEN_R_MODE);

    if (fd == -1)
        return;
    dup2(fd, STDOUT_FILENO);
    close(fd);
}

void pipe_first(data_t *data, command_t *head, int fd[2])
{
    pid_t pid = fork();

    if (pid == -1)
        return (void)my_perror("fork", 1);
    else if (pid == 0) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        choose_bin_buitlin(data, head);
        my_exit(data);
    }
}

void pipe_middle(data_t *data, command_t *head, int fd1[2], int fd2[2])
{
    pid_t pid = fork();

    if (pid == -1)
        return (void)my_perror("fork", 1);
    else if (pid == 0) {
        dup2(fd1[0], STDIN_FILENO);
        dup2(fd2[1], STDOUT_FILENO);
        close(fd1[0]);
        close(fd1[1]);
        close(fd2[0]);
        close(fd2[1]);
        choose_bin_buitlin(data, head);
        my_exit(data);
    }
    close(fd1[0]);
    close(fd1[1]);
}

void pipe_end(data_t *data, command_t *head, int fd[2])
{
    pid_t pid = fork();

    if (pid == -1)
        return (void)my_perror("fork", 1);
    else if (pid == 0) {
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        close(fd[0]);
        if (head->next_delim == S_RIGHT || head->next_delim == D_RIGHT)
            redirect_to_file(head);
        choose_bin_buitlin(data, head);
        my_exit(data);
    }
    close(fd[0]);
    close(fd[1]);
    if (head->next_delim != S_RIGHT && head->next_delim != D_RIGHT)
        data->exit = wait_child(pid);
}

void my_exec_pipe(data_t *data, command_t *current)
{
    if (current->type == BIN && check_perms(current) != 0)
        return;
    if (current->next_delim == PIPE) {
        if (pipe(current->fd) == -1)
            return print_error("42sh", INTERNAL_ERR, 1);
    }
    if (current->prev_delim != PIPE && current->next_delim == PIPE)
        pipe_first(data, current, current->fd);
    else if (current->prev_delim == PIPE && current->next_delim != PIPE) {
        pipe_end(data, current, current->prev->fd);
    } else
        pipe_middle(data, current, current->prev->fd, current->fd);
}