/*
** EPITECH PROJECT, 2020
** shell.h
** File description:
** Header for 42sh
*/

#ifndef SH_H
#define SH_H

#include "my.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <dirent.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#define UNUSED          __attribute__ ((unused))

#define OPEN_R_MODE     S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH
#define OPEN_SR_FLAG    O_RDWR | O_CREAT | O_TRUNC
#define OPEN_DR_FLAG    O_RDWR | O_CREAT | O_APPEND

#define BUILTINS  "exit cd unalias setenv unsetenv history alias env set unset"
#define DELIMS    ";|<>"

#define SETENV_LTRFIRST "Variable name must begin with a letter.\n"
#define SETENV_NONALPHA "Variable name must contain alphanumeric characters.\n"

#define CMD_NOTFOUND    "Command not found.\n"
#define INTERNAL_ERR    "Internal error.\n"
#define ERR_WRONG_ARCH  "Exec format error. Wrong Architecture.\n"
#define ERR_SEGFAULT    "Segmentation fault (core dumped)\n"
#define ERR_FLOATPOINT  "Floating exception (core dumped)\n"

typedef enum delimiter
{
    VOID, PIPE, SEMICOLON, S_RIGHT, S_LEFT, D_RIGHT, D_LEFT, AND, OR
} delimiter;

typedef enum command_type
{
    NOT_FOUND, BIN, BUILTIN
} commmand_type;

typedef struct double_left_redir_storage_s
{
    char *line;
    struct double_left_redir_storage_s *next;
} dlr_storage_t;

typedef struct alias_list_s
{
    char *key;
    char *value;
    struct alias_list_s *next;
} alias_t;

typedef struct command_list_s
{
    int fd[2];
    char **args;
    char *bin_path;
    commmand_type type;
    delimiter next_delim;
    delimiter prev_delim;
    struct command_list_s *next;
    struct command_list_s *prev;
} command_t;

typedef struct local_list_s
{
    char *key;
    char *value;
    char *full_line;
    struct local_list_s *next;
} mylocal_t;

typedef struct env_list_s
{
    char *key;
    char *value;
    char *full_line;
    struct env_list_s *next;
} myenv_t;

typedef struct path_list_s
{
    char *folder;
    struct path_list_s *next;
} mypath_t;

typedef struct history_list_s
{
    char *command;
    int hours;
    int minutes;
    int cmd_index;
    struct history_list_s *prev;
    struct history_list_s *next;
} history_t;

typedef struct lists_struct_s
{
    myenv_t *env;
    mylocal_t *local;
    mypath_t *path;
    history_t *history;
    command_t *commands;
    alias_t *alias;
} lists_t;

typedef struct data_s
{
    lists_t *lists;
    char **env_arr;
    char **builtins;
    char *input;
    char *clean_input;
    int is_exited;
    int exit;
} data_t;

// create_data_struct.c :
data_t *create_data_struct(char **envp);
void fill_path_list(mypath_t **path_head, myenv_t *env_head);

// myenv_handler.c :
int push_in_myenv(myenv_t **head, char *line);

// mypath_handler.c :
int push_in_mypath(mypath_t **head, char *line);

// modify_myenv.c :
char *get_value_by_key(myenv_t *myenv, char *key);
int modify_value_from_key(myenv_t *myenv, char *key, char *value);
void remove_node_from_key(myenv_t **myenv, char *key);

// command_handler.c :
int push_command(data_t *data, char *line, delimiter next, delimiter prev);
int get_cmd_count(command_t *head);

// add_commands_to_list.c :
int add_commands_to_list(data_t *data, char *clean_input);

// bin_research.c :
char *search_in_pwd(char *pwd, char *arg);
char *search_in_mypath(mypath_t *head, char *arg);
char *handle_bin_with_path(char *arg);

// process_user_input.c :
void process_user_input(data_t *data);
void iterate_through_commands(data_t *data);

// clean_user_input.c :
char *clean_user_input(char *input);
char *clean_delim(char *arg);
int check_invalid_redirection(char *arg);
int is_delim(char c);

// backticks :
int check_backticks(data_t *data, char **line);
char *exec_bacticks(data_t *data, char *clear_line);
char *read_file(char *file_path);
char *parse_subcommand(char *full_line);
char *replace_in_backticks(char *full_line, char *results);
int get_size_subcommand(char *full_line);

// execution (folder) :
void my_exec(data_t *data, command_t *head);
void my_exec_pipe(data_t *data, command_t *head);
int wait_child(pid_t child_pid);
int check_perms(command_t *head);
int exec_bin(data_t *data, command_t *head);
void choose_bin_buitlin(data_t *data, command_t *head);

// redirection.c
void left_redir(data_t *data, command_t *cmd);
void right_redir(data_t *data, command_t *cmd, int flag);
void double_left_redir(data_t *data, command_t *cmd);

// dlr_storage_handler.c :
char *get_dlr_input(char *end_str);

// builtins (basics) :
void handle_builtins(data_t *data, char **args);
void add_key_to_myenv(data_t *data, char *key, char *value);
void bt_cd(data_t *data, char **args);
void bt_env(data_t *data, char **args);
void bt_setenv(data_t *data, char **args);
void bt_exit(data_t *data, char **args);

// events_handler
int events_handler(data_t *data);
int contains_events(char *clear_line);
int check_existing_events(char *clear_line, history_t *history);
char *parse_events(char *clear_line, history_t *h_command);
char *get_word_events(history_t *h_command, int nbr_events, int last_events);
int get_events_len(char *line, history_t *h_command);

// bt_local.c
int is_echo_builtin(char **args);
void bt_echo(data_t *data, char **args);
void bt_set(data_t *data, char **args);
void add_key_to_mylocal(data_t *data, char *key, char *value);
void bt_unset(data_t *data, char **args);
void free_local_node(mylocal_t *node);
char *get_value_by_key_local(mylocal_t *mylocal, char *key);
mylocal_t *get_node_by_key_local(mylocal_t *mylocal, char *key);
int modify_value_from_key_local(mylocal_t *mylocal, char *key, char *value);
void remove_node_from_key_local(mylocal_t **mylocal, char *key);
char *get_local_value(char *line, int x, char *value);
int local_str_isvalid(char *str);
char *delete_spaces(char *str, int len);

// bt_history.c
void bt_history(data_t *data, char **args);
void print_history(history_t *history);
void print_part_history(data_t *data, char **args);
int check_history_error(char **args);
int get_history_len(history_t *history);
void check_history_list(history_t **history, char *clear_line);
int push_in_history(history_t **head, char *clear_line);

// bt_alias.c :
void bt_alias(data_t *data, char **args);
void bt_unalias(data_t *data, char **args);
void check_aliases(data_t *data, char *line);

// alias_handler.c :
int push_alias_node(data_t *data, char *key, char *value);
alias_t *get_alias_by_key(alias_t *head, char *key);
void free_alias_list(alias_t *head);

// modify_alias_list.c :
int modify_alias_from_key(alias_t *head, char *key, char *value);
void modify_or_push_alias(data_t *data, char *key, char *value);
void remove_alias_from_key(alias_t **head, char *key);

// print_prompt.c
void print_prompt(data_t *data);
char *get_directory_name(void);
void set_sh(data_t *ptr);
data_t *sh_manager(void *ptr, int mode);
data_t *get_sh(void);

// cleanup.c :
void free_tab(char **tab);
void free_data(data_t *data);
void my_exit(data_t *data);

// free_list.c :
void free_env_node(myenv_t *node);
void free_env_list(myenv_t *head);
void free_path_list(mypath_t *head);
void free_command_list(command_t *head);
void free_dlr_list(dlr_storage_t *head);
void free_history_list(history_t *head);
void free_local_list(mylocal_t *head);

// my_getline.c :
char *my_getline(char **line, int opt);

// my_strtok.c :
char **my_strtok(char *str);
int is_double_delim(char *arg, int i);

// myenv_to_word_array.c
char **myenv_to_word_array(myenv_t *head);

// word_array_utils.c :
int word_array_len(char **tab);
int word_array_contains(char **tab, char *str);
int total_word_array_len(char **tab);
char *word_array_to_string(char **tab);

// print_error.c :
int my_perror(char *str, int code);
void print_error(char *prefix, char *err, int exit_code);

// nbr_of_digits.c
int count_digits(int nbr);

// str_utils.c :
int my_str_contains(char *str, char c);
int my_str_isnumber(char *str);
char *analyse_first_arg(data_t *data, command_t *cmd);
char *concat_two_string(char *str1, char *str2, char *sep);
char **separate_bin_and_path(char *arg);

#endif