/*
** EPITECH PROJECT, 2020
** my_redirection.c
** File description:
** Execute command if next delimiter is a redirection
*/

#include "shell.h"

int send_to_child(char *user_input, int fd[2])
{
    if (!user_input)
        return -1;
    if (pipe(fd) == -1) {
        free(user_input);
        return -1;
    }
    write(fd[1], user_input, strlen(user_input));
    close(fd[1]);
    return 0;
}

void double_left_redir(UNUSED data_t *data, command_t *cmd)
{
    char *user_input = get_dlr_input(cmd->next->args[0]);
    pid_t pid;
    int fd[2];

    if (send_to_child(user_input, fd) == -1)
        return;
    pid = fork();
    if (pid < 0)
        return (void)my_perror("fork", 1);
    else if (pid == 0) {
        dup2(fd[0], STDIN_FILENO);
        choose_bin_buitlin(data, cmd);
    }
    free(user_input);
    data->exit = wait_child(pid);
}

void left_redir(data_t *data, command_t *cmd)
{
    int fd = open(cmd->next->args[0], O_RDONLY);
    pid_t pid;

    if (fd == -1)
        return (void)my_perror(cmd->next->args[0], 1);
    pid = fork();
    if (pid < 0)
        return (void)my_perror("fork", 1);
    else if (pid == 0) {
        dup2(fd, STDIN_FILENO);
        choose_bin_buitlin(data, cmd);
    }
    close(fd);
    data->exit = wait_child(pid);
}

void right_redir(data_t *data, command_t *cmd, int flag)
{
    int fd = open(cmd->next->args[0], flag, OPEN_R_MODE);
    pid_t pid;

    if (fd == -1)
        return (void)my_perror(cmd->next->args[0], 1);
    pid = fork();
    if (pid < 0)
        return (void)my_perror("fork", 1);
    else if (pid == 0) {
        dup2(fd, STDOUT_FILENO);
        choose_bin_buitlin(data, cmd);
    }
    close(fd);
    data->exit = wait_child(pid);
}