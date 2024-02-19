/*
** EPITECH PROJECT, 2020
** backticks_file.c
** File description:
** Clean delimitor from user input
*/

#include "shell.h"

int read_check(FILE *file, long size)
{
    if (fseek(file, 0, SEEK_END) == -1)
        return -1;
    size = ftell(file);
    if (size == -1)
        return -1;
    rewind(file);
    return size;
}

FILE *open_file(char *file_path)
{
    FILE *file = NULL;

    if (!file_path)
        return NULL;
    file = fopen(file_path, "r");
    if (!file)
        return NULL;
    return file;
}

char *create_buf(long size, FILE *file)
{
    char *buf = malloc(sizeof(char) * (size + 1));
    long read_size = 0;

    if (!buf) {
        fclose(file);
        return NULL;
    }
    read_size = fread(buf, sizeof(char), size, file);
    if (read_size != size || read_size == 0) {
        free(buf);
        fclose(file);
        return NULL;
    }
    buf[size - 1] = '\0';
    return buf;
}

char *read_file(char *file_path)
{
    char *buf = NULL;
    long size = 0;
    FILE *file = open_file(file_path);

    if (!file)
        return NULL;
    size = read_check(file, size);
    if (size == -1) {
        fclose(file);
        return NULL;
    }
    buf = create_buf(size, file);
    if (!buf)
        return NULL;
    fclose(file);
    return buf;
}