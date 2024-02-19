/*
** EPITECH PROJECT, 2021
** get_directory.c
** File description:
** Get actual directory name from absolute PWD
*/

#include "shell.h"

int get_last_folder_len(char *dir_name)
{
    int len = strlen(dir_name) - 1;
    int co = 0;

    len -= (len > 1 && dir_name[len] == '/') ? 1 : 0;
    while (len > 0 && dir_name[len--] != '/')
        co++;
    return co;
}

char *get_last_folder(char *actual_dir)
{
    int folder_len = get_last_folder_len(actual_dir);
    char *get_name = malloc(sizeof(char) * (folder_len + 1));
    int index = 0;

    if (!get_name)
        exit(84);
    for (int i = strlen(actual_dir) - folder_len; actual_dir[i] != '\0'; i++)
        get_name[index++] = actual_dir[i];
    get_name[index] = '\0';
    return get_name;
}

char *get_directory_name(void)
{
    char *get_name = NULL;
    char *actual_dir = getcwd(NULL, 0);

    if (!actual_dir)
        return NULL;
    if (my_strcmp(actual_dir, "/") == 0)
        get_name = my_strdup("/");
    else
        get_name = get_last_folder(actual_dir);
    free(actual_dir);
    return get_name;
}