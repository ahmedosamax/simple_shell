#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>


/* FOR R/W BUFFS */
#define R_BUFF_S 1024
#define W_BUFF_S 1024
#define BUFF_FL -1

/* FOR CMD CH */
#define CMD_N 0
#define CMD_O 1
#define CMD_A 2
#define CMD_C 3

/* FOR conv_nums() */
#define CONV_LOWER 1
#define CONV_UNS 2

/* 1 if using SYS GTL */
#define USE_GTL 0
#define USE_ST 0

#define HIST_F	".simple_shell_history"
#define HIST_M	4096

extern char **environ;


/**
 * struct lisststr - linked list
 * @n: the number field
 * @s: a string
 * @next: points to the next node
 */
typedef struct lisststr
{
	int n;
	char *s;
	struct lisststr *next;
} list_str;

/**
 *struct info_pass - contains args to pass to the function
 *@arg: string generated
 *@argv: array of string
 *@p: path of string
 *@argc: the counter of argv
 *@line_counter: the counter of error
 *@ror_n: the exit of code
 *@line_flag: flag of line input
 *@f_name: the file of program
 *@envi: copy of inveron
 *@env: modified copy of enveron
 *@hist: the history n
 *@al: the alias n
 *@env_c: conditon if env changed
 *@state: re the state of command
 *@cmd_buff: double poitner to cmd buffer
 *@cmd_buff_t: cmd type
 *@r_fd: the read op from input
 *@h_counter: line num counter
 */
typedef struct info_pass
{
	char *arg;
	char **argv;
	char *p;
	int argc;
	unsigned int line_counter;
	int ror_n;
	int line_flag;
	char *f_name;
	list_str *env;
	list_str *hist;
	list_str *al;
	char **envi;
	int env_c;
	int state;
	char **cmd_buff;
	int cmd_buff_t;
	int r_fd;
	int h_counter;
} inf;

#define INFO_IN \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct built - contain string and function
 *@t: flag of builtin commmand
 *@f: the func
 */
typedef struct built
{
	char *t;
	int (*f)(inf *);
} built_t;


/* sh_loop.c */
int hash(inf *, char **);
int fi_built(inf *);
void fi_cmd(inf *);
void fo_cmd(inf *);

/* par.c */
int is_cmdd(inf *, char *);
char *duppl_characts(char *, int, int);
char *fi_p(inf *, char *, char *);


int loop_hash(char **);

/* errorss.c */
void ror_puts(char *);
int ror_putchar(char);
int ror_putfd(char c, int fd);
int ror_putsfd(char *str, int fd);

/* sttrings.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* sstringss1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* tokens.c */
char **strtw(char *, char *);
char **strtw2(char *, char);

/* reallloc.c */
char *_memset(char *, char, unsigned int);
void ffre(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* mem.c */
int buff_free(void **);

/* ati.c */
int inter(inf *);
int is_del(char, char *);
int is_abc(int);
int _atoi(char *);

/* errorss1.c */
int ror_atoi(char *);
void ror_print(inf *, char *);
int d_print(int, int);
char *conv_n(long int, int, int);
void rem_comm(char *);

/* builtins.c  */
int my_exit(inf *);
int my_cd(inf *);
int my_help(inf *);

/* builtins1.c */
int my_hist(inf *);
int my_al(inf *);

/*gt_line.c */
ssize_t gt_in(inf *);
int gt_l(inf *, char **, size_t *);
void si_handle(int);

/* gt_info.c*/
void cl_info(inf *);
void st_info(inf *, char **);
void fr_info(inf *, int);

/* envi.c */
char *get_env(inf *, const char *);
int my_env(inf *);
int my_set_env(inf *);
int my_unset_env(inf *);
int pop_env_l(inf *);

/*gt_env.c */
char **get_envi(inf *);
int unset_env(inf *, char *);
int set_env(inf *, char *, char *);

/* hist.c */
char *gt_hist_f(inf *info);
int w_hist(inf *info);
int r_hist(inf *info);
int b_hist_l(inf *info, char *buff, int line_counter);
int ren_hist(inf *info);

/* lsts.c*/
list_str *a_n(list_str **, const char *, int);
list_str *a_n_end(list_str **, const char *, int);
size_t p_l_str(const list_str *);
int del_n_at_indx(list_str **, unsigned int);
void free_l(list_str **);

/* lsts1.c */
size_t list_l(const list_str *);
char **list_t_str(list_str *);
size_t p_list(const list_str *);
list_str *n_strt_w(list_str *, char *, char);
ssize_t gt_n_i(list_str *, list_str *);

/* vrs.c */
int is_ch(inf *, char *, size_t *);
void ch_ch(inf *, char *, size_t *, size_t, size_t);
int rep_al(inf *);
int rep_var(inf *);
int rep_str(char **, char *);
#endif
