/*
** EPITECH PROJECT, 2020
** my_exec.c
** File description:
** Execute given binary if next or previous delimiter is a ';'
*/

#include "shell.h"

int wait_child(pid_t child_pid)
{
    int child_status = 0;

    if (waitpid(child_pid, &child_status, 0) == -1)
        return my_perror("waitpid", 1);
    if (WIFSIGNALED(child_status)) {
        if (WTERMSIG(child_status) == 11) {
            print_error(NULL, ERR_SEGFAULT, 139);
            return 139;
        }
        else if (WTERMSIG(child_status) == 8) {
            print_error(NULL, ERR_FLOATPOINT, 136);
            return 136;
        }
    }
    if (WIFEXITED(child_status))
        return WEXITSTATUS(child_status);
    return 1;
}

int check_perms(command_t *head)
{
    struct stat fstat;

    if (stat(head->bin_path, &fstat) == -1)
        return my_perror("stat", 1);
    if (S_ISDIR(fstat.st_mode)) {
        print_error(head->args[0], "Permission denied.\n", 1);
        return -1;
    } else {
        if (access(head->bin_path, X_OK) != 0) {
            my_perror(head->args[0], 1);
            return -1;
        }
    }
    return 0;
}

int exec_bin(data_t *data, command_t *head)
{
    if (execve(head->bin_path, head->args, data->env_arr) == -1) {
        if (errno != 8)
            my_perror(head->args[0], 1);
        else
            print_error(head->args[0], ERR_WRONG_ARCH, 1);
        my_exit(data);
        return -1;
    }
    return 0;
}

void choose_bin_buitlin(data_t *data, command_t *head)
{
    if (head->type == BUILTIN) {
        handle_builtins(data, head->args);
        my_exit(data);
    } else
        exec_bin(data, head);
}

void my_exec(data_t *data, command_t *head)
{
    pid_t child_pid;

    if (head->type == BUILTIN)
        return handle_builtins(data, head->args);
    if (check_perms(head) != 0)
        return;
    child_pid = fork();
    if (child_pid < 0)
        data->exit = my_perror("fork", 1);
    else if (child_pid == 0) {
        if (exec_bin(data, head) != 0)
            return;
    }
    data->exit = wait_child(child_pid);
}