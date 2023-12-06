#ifndef header
#define header

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* buffers */
#define READ_BUFFERSIZE 1024
#define WRITE_BUFFERSIZE 1024
#define BUFFER_FLUSH -1

/* command */
#define CMD_NORM   0
#define CMD_OR     1
#define CMD_AND    2
#define CMD_CHAIN  3

#define LOWERCASE_CONVERT   1
#define UNSIGNED_CONVERT    2

#define GETLINE 0
#define STRTOK  0

#define HISTORY_FILE      ".simple_shell_history"
#define HISTORY_MAX       4096

extern char **environ;

/**
 * struct strlist - structure singly linked list
 * @num: field numbers
 * @str: the strings
 * @next: next node to points
 */

typedef struct strlist
{
	int num;
	char *str;
	struct strlist *next;
} lst_t;

/**
 * struct passinginfo - Incorporates pseudo-arguments for a function,
 * ensuring a standardized prototype for a pointer structure.
 * @ag: string generated from getline containing arguements
 * @argv: argument array
 * @path: string path for the current command
 * @argc: argument count
 * @ln_count: error count
 * @error_num: error code for exit()s
 * @ln_flag: if on count this line of input
 * @filename: filename for the program
 * @env: linked list copy of environ
 * @environ: custom modified copy of environ from linked list env
 * @history: history node
 * @alias: alias node
 * @env_changed: changed environ
 * @status: return status of the last executed command
 * @cmd_buffer: address of pointer to command buffer on chaining
 * @cmd_buffer_type: CMD_type ||, &&, ;
 * @readfdes: file discriptor from which to read line input
 * @history_count: history for line number count
 */

typedef struct passinginfo
{
	unsigned int ln_count;
	int status;
	char *filename;
	lst_t *env;
	int error_num;
	lst_t *alias;
	lst_t *history;
	char *ag;
	char **argv;
	char *path;
	int argc;
	char **environ;
	int env_changed;
	int readfdes;
	int history_count;

	int ln_flag;
	char **cmd_buffer;
	int cmd_buffer_type;
} psinfo_t;

#define INIT_INFO \
{0, 0, NULL, NULL, 0, NULL, NULL, NULL, NULL, NULL, 0, NULL, 0, 0, 0, \
	0, NULL, 0}

/**
 * struct builtin - Including inherent string and its associated function
 * @type: builtin flag command
 * @funct: function
 */

typedef struct builtin
{
	char *type;
	int (*funct)(psinfo_t *);
} builtin_tab;

/* shell_exec_cmd.c */
int main_shell(psinfo_t *k, char **argv);
int builtin_cmd(psinfo_t *k);
void cmd_path(psinfo_t *k);
void exec_fork(psinfo_t *k);
int exec_cmd(psinfo_t *k, char *path);

/* manip_string.c */
char *char_dup(char *s, int strt, int stp);
char *find_cmd_path(psinfo_t *k, char *s, char *cmd);
void exec_puts(char *str);
int exec_putchar(char c);
int putchar_fdes(char c, int fdes);

/* manip_string1.c */
int puts_fdes(char *str, int fdes);
int string_len(char *s);
int string_cmp(char *str1, char *str2);
char *strt(const char *str, const char *substr);
char *string_cat(char *destination, char *source);

/* manip_string2.c */
char *string_copy(char *destination, char *source);
char *string_dup(const char *str);
void _puts(char *str);
int _putchar(char c);
char *copy_strn(char *destination, char *source, int a);

/* manip_string3.c */
char *concat_str(char *deatination, char *source, int a);
char *char_str(char *s, char c);
char **tokenstr(char *str, char *del);
char **strtoken(char *str, char del);
char *set_memory(char *s, char sa, unsigned int a);

/* memory_mgt.c */
void free_str(char **sa);
void *mem_realloc(void *pointer, unsigned int o_size, unsigned int n_size);
int free_pointer(void **pointer);

/* i/o_ops.c */
int shell_int(psinfo_t *k);
int shell_delim(char c, char *del);
int cmp_char(int i);
int atoi_char(char *s);
int atoi_err(char *s);

/* i/o_ops1.c */
void err_msg(psinfo_t *k, char *errstr);
int dec_print(int i, int fdes);
char *itoa_int(long int number, int base, int flgs);
void del_comms(char *buff);

/* builtin_cmd.c */
int exit_shell(psinfo_t *k);
int cd_shell(psinfo_t *k);
int help_shell(psinfo_t *k);
int history_shell(psinfo_t *k);

/* builtin_cmd1.c */
int alias_unset(psinfo_t *k, char *str);
int alias_set(psinfo_t *k, char *str);
int get_alias(lst_t *node);
int alias_shell(psinfo_t *k);

/* shell_misc.c */
int chain_delim(psinfo_t *k, char *buff, size_t *p);
void chain_check(psinfo_t *k, char *buff, size_t *p, size_t j, size_t length);
int rep_alias(psinfo_t *k);
int rep_variable(psinfo_t *k);
int rep_string(char **o, char *n);

/* file_io_hist.c */
ssize_t get_lninput(psinfo_t *k);
int get_nxtline(psinfo_t *k, char **pointer, size_t *length);
void block_ctrlc(__attribute__((unused))int block_num);
void init_info(psinfo_t *k);
void set_field_info(psinfo_t *k, char **sa);

/* file_io_hist1.c */
void free_field_info(psinfo_t *k, int all);
char *getenv_val(psinfo_t *k, const char *name);
int print_env(psinfo_t *k);
int set_env(psinfo_t *k);
int un_setenv(psinfo_t *k);

/* file_io_hist2.c */
int fill_env_list(psinfo_t *k);
char **getenv_list(psinfo_t *k);
int _unsetenv(psinfo_t *k, char *variable);
int _setenv(psinfo_t *k, char *variable, char *value);
char *file_history(psinfo_t *k);

/* file_io_hist3.c */
int create_history(psinfo_t *k);
int read_history_file(psinfo_t *k);
int add_history(psinfo_t *k, char *buff, int ln_count);
int num_history(psinfo_t *k);

/* file_io_histmini.c */
ssize_t input_buffer(psinfo_t *k, char **buff, size_t *length);
ssize_t read_buffer(psinfo_t *k, char *buff, size_t *s);

/* linked_list_ops.c */
lst_t *start_node(lst_t **top, const char *string, int num);
lst_t *end_node(lst_t **top, const char *string, int num);
size_t print_str_list(const lst_t *d);
int del_node(lst_t **top, unsigned int index);
void free_link_list(lst_t **top_pointer);

/* linked_list_ops1.c */
size_t get_listlen(const lst_t *d);
char **list_to_str(lst_t *top);
size_t get_list(const lst_t *d);
lst_t *find_start_node(lst_t *node, char *affix, char c);
size_t get_index(lst_t *top, lst_t *node);

#endif

