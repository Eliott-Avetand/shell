/*
** EPITECH PROJECT, 2020
** bin_research.c
** File description:
** Research given bin in PWD or PATH folders
*/

#include "shell.h"

char *iterate_through_dir(char *path, char *arg)
{
    DIR *dir = opendir(path);
    struct dirent *dirent;

    if (!dir)
        return NULL;
    dirent = readdir(dir);
    while (dirent != NULL) {
        if (my_strcmp(dirent->d_name, arg) == 0) {
            closedir(dir);
            return concat_two_string(path, arg, "/");
        }
        dirent = readdir(dir);
    }
    closedir(dir);
    return NULL;
}

char *search_in_pwd(char *pwd, char *arg)
{
    char *bin_path;

    if (!pwd)
        return NULL;
    bin_path = concat_two_string(pwd, arg + 1, "/");
    if (!bin_path)
        return NULL;
    if (access(bin_path, F_OK) != 0) {
        free(bin_path);
        return NULL;
    }
    return bin_path;
}

char *search_in_mypath(mypath_t *head, char *arg)
{
    mypath_t *current = head;
    char *path = NULL;
    DIR *dir;

    if (my_str_contains(arg, '/') >= 1)
        return handle_bin_with_path(arg);
    while (current != NULL) {
        dir = opendir(current->folder);
        if (dir) {
            path = iterate_through_dir(current->folder, arg);
            closedir(dir);
        }
        if (path != NULL)
            return path;
        current = current->next;
    }
    return NULL;
}

char *handle_bin_with_path(char *arg)
{
    char *cmd = NULL;

    if (access(arg, F_OK) != 0)
        return NULL;
    cmd = my_strdup(arg);
    if (!cmd)
        return NULL;
    return cmd;
}