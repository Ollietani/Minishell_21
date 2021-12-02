/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:21:57 by myael             #+#    #+#             */
/*   Updated: 2021/12/02 21:02:05 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include "libft.h"

int	g_return_code;

typedef struct s_data
{
	char			**command;
	int				in;
	int				out;
	char			*hr_name;
	int				num;
	int				err;
	struct s_data	*next;
}				t_data;

typedef struct s_hd
{
	char		**argv;
	char		**envp;
	int			argc;
	int			hd;
	char		*file;
	const char	*str;
	int			ret;
	char		buf[255];
	char		**hd_argv;
}	t_hd;

typedef struct s_fd
{
	char	**com;
	char	**cmd;
	char	**path;
	int		**fds;
	int		*pids;
	int		size;
	int		hd;
}	t_fd;

typedef struct s_e
{
	char		*content;
	struct s_e	*next;
}				t_e;

typedef struct s_all
{
	char	*pwd;
	char	*old_pwd;
	int		amount;
	t_e		*env;
	t_data	*s;
}				t_all;

typedef struct s_utils
{
	char	*pwd;
	char	*old_pwd;
	int		amount;
}				t_utils;

// main.c //

void	add_pwd_data(t_utils *all, t_e *env);

				// SIGNALS //

// signals.c //
void	handle_sigint(void);
void	main_signals_made(void);
void	child_signals(void);
void	signal_for_heredoc(void);
void	ignore_signals(void);

// signals_2.c //
void	signal_for_main_with_fork(void);
void	handle_sigint_fork(void);
void	handle_sigquit_fork(void);

					// UTILIS //

// free_data.c //
void	ft_clear_data(t_data **s);
void	free_double_massive(char **data);

// utilis.c //
int		pipe_in_data(t_list *data);
int		data_is_pipe(t_list *list);
int		check_pipes_amount_list(t_list*data);
int		ft_find_data(t_list *data, char *cont, int len);
char	*ft_find_flag(t_list *data);

// utilis2.c //
int		check_if_str_num(char *data);
void	error_with_std_function(int num);

// lists_env.c //
void	ft_envadd_back(t_e **lst, t_e *new);
t_e		*ft_envnew(char *content);
t_e		*ft_envlast(t_e *lst);
int		ft_envsize(t_e *lst);

					// PARSING //

// parsing_start.c //
void	parse_execute_commands(char *cmd, t_utils *utils, t_e **env);
void	init_data_ints(t_list *data);

// parsing.c //
void	split_commands(char *cmd, t_list **data);
int		check_quote(char *cmd, int i, char quote);
char	*add_data_to_list(char *cmd, int i, t_list **data);
char	*split_special_symbols(t_list **data, char *cmd, int i);
int		check_char_type(char y);

// parsing2.c //
void	check_if_path_not_expand(t_list *data, t_e *env);
void	check_if_change(t_list **data, t_e *env);
void	check_data(t_list **data, t_e *env);

// parsing3.c //
void	clean_commands(t_list *data, t_e *env);
void	check_arg(t_list *data, t_e *env);
int		change_one_quote(t_list *data, int start, char *str);
int		change_double(t_list *data, int start, char *str, int finish);
char	*do_change_path(t_list *data, char *str, int *i, t_e *env);

// parsing4.c //
int		delete_double_quotes(t_list *data, int start, char *str, t_e *env);
int		check_path_data(t_list *data, int i, char *str, t_e *env);
int		data_change_path(t_list *data, int i, char *str, t_e *env);
char	*check_in_env(char *var, t_e *env);
int		check_path(int i, char *str);

// parsing5.c //
int		data_dollar_num(t_list *data, int i, char *str);
int		data_dollar_question(t_list *data, int i, char *str);
int		check_syntax_errors(t_list *data);
int		check_only_redirect_pipe(t_list *data);
int		if_there_is_error(t_list *data);

// parsing6.c //
int		print_error(char type);
int		check_repeated_specs(t_list *data);
int		ft_pipe_error(t_list *data);
int		both_data_spec_symbols(char *copy, char *next);
int		data_pipe_or_redirect(t_list *data);

				// PRE_EXECUTING //

// lists_for_new_struct.c //
int		init_new_struct(t_list *data, t_data **s, t_utils *utils);
void	add_back_data(t_data **s, t_data *new);
t_data	*ft_lst_data(t_data *data);
t_data	*lst_new_data(int num);

// utilis_for_redirects.c //
int		ft_amount_of_args(t_list *data);
int		data_redirect(t_list *data);
int		data_redirect_out(t_list *data);
int		data_redirect_in(t_list *data);
int		data_redirect_and_heredoc(t_list *data);

// heredoc.c //
void	start_new_readline(t_list *data, int save, t_data *s);
int		check_if_saved_in(t_list *data);
t_list	*check_type_readline(t_list *data, t_data *s);
void	start_heredoc(t_list *list, t_data *s);
void	child_proc_heredoc(t_list *data, int save, t_data *s);

// heredoc2.c //
void	open_file_for_heredoc(t_data *s);
char	*create_hd(const char *str);

// made_new_struct.c //
void	ft_made_new_struct(t_list *list, t_data *s);
t_list	*made_massive_command(t_list *list, int amount, t_data *s);
t_list	*skip_pipe_data(t_list *list, int amount, t_data *s);
t_list	*skip_error_process(t_list *list, t_data *s);
void	add_command_and_args(t_list *list, t_data *s);

// for_new_struct.c //
int		count_amount_of_args(t_list *list);

// made_redirects_data.c //
void	made_redirects(t_list *list, t_data *s);
t_list	*open_out_files(t_list *list, t_data *s);
t_list	*open_in_files(t_list *list, t_data *s);
t_list	*error_with_redirect(t_list *list, t_data *s);

// for_redirects.c //
int		check_if_not_last_redirect_in(t_list *list);
int		check_if_not_last_redirect_out(t_list *list);
t_list	*open_redirect(t_list *list, t_data *s);
t_list	*error_ambitious_data(t_list *list, t_data *s);

					// BUILD_INS //

// build_in.c //
int		check_if_build_in_or_null(t_e **env, t_data *s, t_utils *utils,
			int flag);
void	choose_build_in_function(t_e **env, t_data *s, t_utils *utils,
			int flag);
void	made_new_minishell(t_e *env);
int		child_minishell(t_e *env);

// echo.c //
void	echo_build_in(t_data *s);
int		for_echo(char **command, int a, int *flag);

// pwd.c //
void	pwd_build_in(t_data *s, t_utils *utils);

// cd.c //
void	cd_build_in(char **cmd, t_e *env, char *pwd);
char	*get_address(void);
void	change_env_pwds(t_utils *utils, t_e *env);

// export.c //
void	export_build_in(t_e **env, t_data *s);
void	print_export_data(char **data, t_data *s);
void	sort_export_data(t_e *env, t_data *s);
int		check_for_error_data(char *data, char c);
void	add_new_data(t_e **env, char *command);

// env.c //
void	env_build_in(t_e *env, t_data *s);
t_e		*find_env_data(t_e *env, char *data);
t_e		*add_env(char **envp);
void	change_env_data(t_e **env);

// exit.c //
void	exit_build_in(t_data *s);
int		check_if_str_num(char *data);
void	exit_minishell(void);

// unset.c //
void	unset_build_in(t_data *s, t_e **env);
void	change_data_in_list(t_e *env, char *data);

				// EXECUTE //

// pipex.c //
void	pipex(t_data *s, t_utils *utils, t_e **env);
void	single_command(t_e **env, t_data *s, t_utils *utils, t_fd *pipex);
void	check_fds(t_data *s);
void	waitpid_and_return(t_fd *pipex, int count);
void	multiple_commands(t_e **env, t_data *s, t_utils *utils, t_fd *pipex);

// pipex_1.c //
void	count_pipes(t_fd *pipex, t_utils *utils);
void	child_process(t_fd *pipex, t_data *s, t_utils *utils, t_e **env);
char	**build_envp(t_e *env);
void	child(t_fd *pipex, t_data *s, t_utils *utils, t_e **env);

// pipex_2.c //
void	close_fd(int **fds);
void	memory_alloc(t_fd *pipex, t_utils *utils);
void	close_inout(t_data *s);
void	if_no_first_command(t_data *s);

// fill_list.c //
void	middle_child(t_data *s, t_fd *pipex);
void	last_child(t_data *s, t_fd *pipex);
void	first_child(t_data *s, t_fd *pipex);
void	do_process(t_data *s, t_utils *utils, t_fd *pipex);

// parse_cmdstr.c //
char	*add_dir(t_fd *descriptor, char **cmd, char **envp);
char	*check_commands(t_fd *descriptor, char *cmd);
char	*no_path(t_fd *descriptor, char **cmd);

// error.c //
void	error(int num, char *str);

#endif
