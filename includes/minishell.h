/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 03:38:55 by simonp            #+#    #+#             */
/*   Updated: 2025/02/17 18:25:46 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include <limits.h>
# include <signal.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <linux/types.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <time.h>
# include <readline/history.h>
# include <readline/readline.h>

# define PATH_MAX	4096

extern int	g_exit_loop;

//Enum
typedef enum s_argument
{
	ARGUMENT,
	BUILTIN,
	COMMAND,
	ENDOFFILE,
	EXPANSION,
	FILENAME,
	FOLDER,
	OPERATOR,
	HERE_DOC,
	OPTION,
	PIPE,
	PROGRAM,
	STDIN,
	STDOUT,
	STDOUT_ADD,
	STRING,
	UNDEFINE,
	VARIABLE,
	FLAG,
	NEW_UNDEFINE,
	HEREADD,
	STDIN_OUT,
	IS_TAB,
}	t_argument;

typedef struct s_pars
{
	int		pipe;
	int		link;
	int		i;
	int		pos;
	int		q;
	char	quote;
}	t_pars;

//Token struct
typedef struct s_token
{
	int				token;
	int				link;
	char			*type;
	bool			single_q;
	bool			double_q;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

// Parsing struct W.I.P.
typedef struct s_node
{
	int				pos;
	char			*type;
	char			*str;
	struct s_node	*left;
	struct s_node	*right;
	struct s_node	*next;
}	t_node;

typedef struct s_env_link
{
	char				*ev;
	struct s_env_link	*next;
	struct s_env_link	*prev;
}	t_env_link;

//Signal
typedef struct s_signal
{
	int		exit_flag;
}	t_signal;

typedef struct s_command
{
	char	*cmd_path;
}	t_command;

typedef struct s_here_doc
{
	char	*line;
	char	*limite;
	int		here_pipe[2];
}	t_here_doc;

typedef struct s_builtin
{
	char		**echo;
	int			exit;
	char		directory[PATH_MAX];
	char		last_directory[PATH_MAX];
	char		oldpwd[PATH_MAX];
	char		change[PATH_MAX];
	char		**arg_export;
	char		**arg_unset;
	t_env_link	*env_link;
}	t_builtin;

typedef struct s_error
{
	bool			status;
	bool			syntax;
	bool			keyword;
	bool			token_quotes;
	bool			env_null;
}	t_error;

typedef struct s_dup
{
	int		stdin_fd;
	int		stdout_fd;
	int		append_fd;
	int		here_doc;
	int		error_stdout;
}	t_dup;

typedef struct s_exec
{
	int			prev_pipe;
	pid_t		pid;
	int			pipe[2];
	int			status;
	int			exit_code;
	int			fd[2];
	int			stdin_backup;
	int			stdout_backup;
	t_dup		file;
	t_command	cmd;
	t_env_link	env_link;
	t_here_doc	here_doc;
	t_token		*token;
}	t_exec;

typedef struct s_redirection
{
	int		type;
	int		fd;
}	t_redirection;

typedef struct s_execution
{
	int				id;
	char			*cmd;
	char			**args;
	int				heredoc_count;
	int				*heredoc_fds;
	int				redirection_count;
	t_redirection	*redirections;
	int				pipe_in;
	int				pipe_out;
	int				pipe_fd[2];
}	t_execution;

//Main Struct
typedef struct s_minishell
{
	int					save_pipe_in;
	bool				error_stdout;
	int					stdin_backup;
	int					stdout_backup;
	int					pid;
	int					exec_count;
	bool				status;
	bool				syntax;
	char				*prompt;
	bool				keyword;
	bool				token_quotes;
	bool				env_null;
	t_builtin			builtin;
	t_command			cmd;
	t_dup				fd;
	t_pars				pars;
	t_signal			signal;
	t_token				*token;
	t_env_link			*env_link;
	t_argument			arg;
	t_error				error;
	t_exec				exec;
	t_execution			*execution;
}	t_minishell;

// CHECKER

// checker.c
void		ft_splitting(t_token *tmp, const char *str, int start, int end);
void		ft_checker(t_minishell *minishell);
// deleting.c
void		ft_delete_first_node(t_token **head);
void		ft_delete_node(t_token *node);
t_token		*ft_delete_leftover(t_minishell *minishell);
t_token		*ft_delete_tab_nodes(t_minishell *minishell);
// is.c
bool		ft_is_pipe(t_token *tmp);
bool		ft_is_std_in(t_token *tmp);
bool		ft_is_std_out(t_token *tmp);
bool		ft_is_std_out_add(t_token *tmp);
bool		ft_is_here_doc(t_token *tmp);
// env_var.c
int			ft_is_exit_code(t_minishell *minishell, t_token *token, int i);
void		ft_check_expand(t_minishell *minishell);
// second_token.c
void		ft_second_token(t_minishell *minishell);
// third_token_utils.c
bool		is_sep_in_ll(t_token *token);
// third_token.c
bool		ft_is_separator_bis(char c);
void		ft_fourth_token(t_minishell *minishell);
t_token		*ft_third_token(t_minishell *minishell);
// utils_checker_bis_bis.c
void		navi_link(t_minishell *minishell);
t_token		*erase_link(t_minishell *minishell);
// utils_checker_bis.c
void		ft_find_tab(t_minishell *minishell);
bool		error_sep(t_minishell *minishell, t_token *token);
// utils_checker.c
int			ft_do_idk(t_token *tmp, int i, int len);
void		ft_add_separator(t_token *tmp, int i);
void		ft_find_separator(t_token *token);
bool		ft_check_separate(t_token *tmp);
// utils_env_var_bis_bis.c
void		check_exit_code(t_minishell *minishell, t_token *token, int i);
bool		find_nbr(char *str);
char		*new_t_type(char *str);
// utils_env_var_bis.c
bool		ft_count_d(char *str, int i);
char		*ft_do_join(char *new_str, char *var_content, char c, char type);
void		ft_del_false_var(t_token *token, char *var_name, int i);
char		*ft_exit_code_tmp(t_token *token, int i);
void		ft_exit_code_join(t_minishell *minishell, t_token *token, int i);
// utils_env_var.c
char		*ft_get_var_name(char *token_type);
char		*ft_get_var_content(t_env_link *env, char *var_name);
bool		ft_check_name(char *token_type, char *var_name, int pos);
bool		ft_free_false(char *var_name);
// utils_second_token.c
bool		ft_keywords(t_token *tmp);
bool		ft_isbuiltin(t_token *tmp);
bool		ft_isfile(t_token *tmp);
bool		ft_iscmd(t_token *tmp);
// utils.c
bool		ft_is_separator(char c);
void		ft_adding_node(t_token *current, t_token *new_node);
int			token_before(t_token *tmp);
bool		cmd_before(t_token *tmp);
bool		check_before(t_token *tmp);

// ENV

// builtin_prt2.c
void		ft_env_export(t_minishell *minishell, t_env_link *env);
void		ft_export(t_minishell *minishell, char **str);
void		ft_unset(t_minishell *minishell, char **str);
void		ft_cd(t_minishell *minishell, t_builtin *builtin);
// builtin_prt3.c
void		ft_do_exit_bis(t_minishell *minishell, t_token *token);
bool		ft_is_valid_id(char *str);
bool		is_just_name(char *str);
bool		is_valid_name(const char *str);
// builtin_prt4.c
bool		is_valid_char(char c);
bool		ft_its_the_name(char *ev, char *unset);
// builtin_tool.c
bool		edit_oldpwd(t_minishell *minishell, t_env_link **env);
bool		edit_pwd(t_minishell *minishell, t_env_link **env);
bool		already_env(t_minishell *minishell, char *str);
bool		ft_echo_tool(char *str);
// builtin.c
void		ft_exit(t_minishell *minishell, int exit_code);
void		ft_do_exit(t_minishell *minishell, t_token *token);
void		ft_env(t_minishell *minishell, t_env_link *env);
void		ft_echo(t_builtin *builtin);
void		ft_pwd(t_builtin *builtin);
// edit
bool		ft_init_shlvl(t_minishell *minishell, t_env_link **env);
// env.c
bool		check_env(char **ev);
void		init_env(t_minishell *minishell, char **ev);
//export_tool.c
bool		check_double(t_env_link	*env, char *str);
int			lim_name(t_env_link	*env, char *str);
bool		edit_env(t_minishell *minishell, t_env_link	*tmp, \
			char *str, size_t lim);
// node_env.c
void		clear_link_env(t_env_link **lst_env);
t_env_link	*new_env(char *type);
void		add_env(t_env_link **lst, t_env_link *new);
//cd_tool.c
int			cd_arg_count(t_token *token);
bool		cd_check_arg(t_token *token);

// ERROR

// error_checker.c
void		ft_do_error(t_minishell *minishell, int token);
bool		ft_error_checker(t_minishell *minishell);
// error_system.c
void		pid_error(t_minishell *minishell);

// EXEC
//builtin_utils.c
void		ft_pipe_builtin(t_minishell *minishell, t_token *token, \
	t_execution *execution, int pipe_fds[2]);
//children_tool.c
void		free_resseource_children(t_minishell *minishell, int pipe_fds[2]);
//close_fd_children.c
void		close_std(t_minishell *minishell);
void		close_stdin(t_minishell *minishell);
void		close_stdout(t_minishell *minishell);
void		close_fd(t_minishell *minishell);
//close_fd_children_prt2.c
void		free_redirections_heredoc(t_execution *exec);
void		free_redirections_std(t_execution *exec);
//commande.c
void		execout(t_minishell *minishell, t_execution *execution);
void		get_cmd_test(t_minishell *minishell, t_execution *execution);
bool		find_path_test(t_minishell *minishell, t_execution *execution);
//commande_part2.c
void		access_program_test(t_minishell *minishell, t_execution *execution);
void		exec_program_test(t_minishell *minishell, t_execution *execution);
//exec.c
bool		exec_without_pipe(t_minishell *minishell);
bool		exec_single(t_minishell *minishell);
void		last_exec(t_minishell *minishell, t_token *token, \
			t_execution *execution);
bool		exec(t_minishell *minishell, t_token *token);
//exec_part2.c
void		fork_exec(t_minishell *minishell, t_token *token, \
	t_execution *execution,	int pipe_fds[2]);
//exec_tool.c
void		close_pipe_fd(int pipe_fds[2]);
bool		create_pipe(t_minishell *minishell, int pipe_fds[2]);
void		dup_in(t_minishell *minishell, int pipe_fds[2]);
void		dup_out(t_minishell *minishell, int pipe_fds[2]);
void		exec_cmd_and_builtin(t_minishell *minishell, t_token *tmp);

// system.c
void		get_exit_status(t_minishell *minishell);
// util.c
char		*put_str_env(t_minishell *minishell, t_env_link **env, char *str);
int			count_nodes(t_env_link *env);
char		**convert_env_to_array(t_minishell *minishell, t_env_link *head);

// IO
//dup_fd.c
bool		dup_fd_out(t_minishell *minishell, t_execution *tmp_exec, \
			int pipe_fds[2]);
bool		dup_fd(t_minishell *minishell, t_execution *execution, \
			int pipe_fds[2]);
//here_doc.c
void		write_pipe(t_minishell *minishell, char *line, int pipe_fd);
bool		check_lim_for_exit(t_minishell *minishell, char *line, \
			t_token *token, int pipe_fds[2]);
void		here_doc(t_minishell *minishell, t_execution *exec, \
			t_token *token, int heredoc_index);
bool		open_std(t_minishell *minishell, t_token *redirect, \
			t_redirection *redir);
bool		open_here_doc(t_minishell *minishell, t_execution *exec, \
			t_token *token, int heredoc_index);
//open_fd.c
bool		init_fd(t_minishell *minishell, t_token *token, int current_exec);
bool		open_stdin(t_minishell *minishell, t_token *redirect, \
			t_redirection *redir);
bool		open_stdout(t_minishell *minishell, t_token *redirect, \
			t_redirection *redir);
//expansion-heredoc.c
char		*replace_env_variables(t_minishell *minishell, char *line);
// stderr.c
void		write_str(char *str, int fd);
void		write_str2(char *str, char *str2, int fd);

// builtin_utils.c
void		ft_do_builtin(t_minishell *minishell, t_token *token);
int			ft_len_args(t_token *token);
int			ft_count_flags(t_token *token);
// do_builtin.c
void		ft_do_cd(t_minishell *minishell, t_token *token, \
			t_builtin *directory);
void		ft_do_echo(t_minishell *minishell, t_token *token);
void		ft_do_env(t_minishell *minishell, t_env_link *env, t_token *token);
void		ft_do_export(t_minishell *minishell, t_token *token);
void		ft_do_unset(t_minishell *minishell, t_token *token);

// SIGNALS

// signal.c
//void		ft_sig_handler(int signal);
void		second_sig(void);
void		main_signal(t_minishell *minishell);

// signal_here_doc.c
void		ft_exit_here_doc(int signal);
void		stop_child(t_minishell *minishell, t_token *token, char *line);

// STRUCT

// monitoring_struct.c
void		clear_exit(t_minishell *minishell);
void		init_minishell(t_minishell *minishell, char **ev);
void		prompt_init(t_minishell *minishell);
bool		exit_minishell(t_minishell *minishell);
// reset.c
void		free_execution(t_execution *exec, int cmd_count);
void		free_all_executions(t_minishell *minishell);
void		reset(t_minishell *minishell);
void		free_redirections(t_execution *exec);

// TOKEN

// lexer_prt2.c
bool		isbuiltin(t_minishell *minishell, t_token *token, char *promt);
bool		isexpansion(t_minishell *minishell, char *promt);
bool		isfile(t_minishell *minishell, t_token *token, char *promt);
bool		ispipe(t_minishell *minishell, char **promt, char *arg);
bool		issdtout_add(t_minishell *minishell, char **promt, char *arg);
// lexer_tool.c
char		*ft_strchr_without_end(const char *s, int c);
bool		count_keyword(char *arg);
bool		count_multi_keywords(char *arg);
// lexer.c
bool		isstdin(t_minishell *minishell, char **promt, char *arg);
bool		isstdout(t_minishell *minishell, char **promt, char *arg);
bool		is_here_doc(t_minishell *minishell, char **promt, char *arg);
bool		iscmd(t_minishell *minishell, t_token *token, char *promt);
// quotes.c
bool		check_start_end(t_minishell *minishell, char *prompt);
void		ft_check_quotes(t_minishell *minishell, char **promt, char *dest);
// node_link.c
void		add_data(t_token **lst, t_token *new, bool s_quote, bool d_quote);
t_token		*new_token(int token, char *type);
void		clear_link_token(t_token **lst_token);
// quotes_utils_bis_bis_bis.c
int			incr_q(char *new_dest, char quote, int q, int i);
bool		to_find_quote(char *dest);
bool		ft_is_only_quotes(char *dest);
bool		check_prblm_quotes(char *str);
void		ft_add_data_and_true(t_minishell *minishell, \
			t_token *token, char quote);
// quotes_utils_bis_bis.c
char		ft_find_next_quote(char *str, int i);
void		ft_str_quotes(t_minishell *minishell, char *dest, \
	int i, char quote);
int			ft_counting_whole_quote(char *dest, char quote);
int			ft_is_there_sep(t_minishell *minishell, char *dest, \
	char quote, int pos);
// quotes_utils_bis.c
char		*rid_of_glued_quotes(char *dest);
void		ft_data_adding(t_minishell *minishell, t_token *token, char quote);
bool		check_closed(char *prompt);
// quotes_utils.c
int			count_quote(const char *str, int c);
int			ft_len_without_quotes(char *dest);
char		ft_get_first_quote(char *dest);
int			find_first_quote(char *str);
int			find_last_quote_index(char *str);
//str_quotes_utils.c
void		change_struct_data(t_minishell *minishell, t_token *token);
void		add_the_new_token(t_minishell *minishell, char *dest, \
			char *tmp, int x);
bool		do_q(t_minishell *minishell, char *dest, char quote, int i);
// token_err.c
void		error_lexer(t_minishell *minishell);
void		error_quote(t_minishell *minishell);
// token_utils.c
void		printer_list(t_token **head);
int			last_token(t_token *lst);
// token.c
void		ft_token(t_minishell *minishell);
// unquoted_var_utils.c
bool		is_var_name(t_minishell *minishell, char *name);
char		*get_var_name_quotes(char *str, char quote, int i);
// unquoted_var.c
char		*find_unquoted_var(t_minishell *minishell, char *str, char quote);

// PARSING
// parsing.c
bool		init_current_exec(t_minishell *minishell, t_token *token, \
			int current_exec);
bool		init_arg_cmd(t_minishell *minishell, t_token *token, \
			int current_exec);
bool		allocade_struct_fd(t_minishell *minishell, t_execution \
	*current, t_token *token);
bool		init_fd_struct(t_minishell *minishell, t_token *token, \
			int current_exec);
// parsing_tool.c
int			count_cmd(t_minishell *minishell);
int			count_std(t_token *token);
int			count_here_doc(t_token *token);
int			count_args_or_flags(t_token *token);
char		*find_cmd(t_token *token);
// builtin_utils.c
void		ft_do_builtin(t_minishell *minishell, t_token *token);
int			ft_len_args(t_token *token);
int			ft_count_flags(t_token *token);
// do_builtin.c
void		ft_do_cd(t_minishell *minishell, t_token *token, \
			t_builtin *directory);
void		ft_do_echo(t_minishell *minishell, t_token *token);
void		ft_do_env(t_minishell *minishell, t_env_link *env, t_token *token);
void		ft_do_export(t_minishell *minishell, t_token *token);
void		ft_do_unset(t_minishell *minishell, t_token *token);
// init_struct_cmd.c
bool		init_structure_cmd(t_minishell *minishell);

#endif
