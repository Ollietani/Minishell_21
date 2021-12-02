/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:49:17 by myael             #+#    #+#             */
/*   Updated: 2021/12/02 21:01:22 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	choose_build_in_function(t_e **env, t_data *s, t_utils *utils, int flag)
{
	char	*cmd;

	cmd = s->command[0];
	if (!ft_strncmp(cmd, "echo", 5))
		echo_build_in(s);
	else if (!ft_strncmp(cmd, "pwd", 4))
		pwd_build_in(s, utils);
	else if (!ft_strncmp(cmd, "env", 4))
		env_build_in(*env, s);
	else if (!ft_strncmp(cmd, "export", 7))
		export_build_in(env, s);
	else if (!ft_strncmp(cmd, "exit", 5))
		exit_build_in(s);
	else if (!ft_strncmp(cmd, "unset", 6))
		unset_build_in(s, env);
	else if (!ft_strncmp(cmd, "cd", 3))
	{
		cd_build_in(s->command, *env, utils->pwd);
		change_env_pwds(utils, *env);
	}
	close_inout(s);
	if (flag == 1)
		exit(EXIT_SUCCESS);
}

int	check_if_build_in_or_null(t_e **env, t_data *s, t_utils *utils, int flag)
{
	char	*cmd;

	if (!s->command)
	{
		close_inout(s);
		return (1);
	}
	cmd = s->command[0];
	if (!ft_strncmp(cmd, "cd", 3) || !ft_strncmp(cmd, "unset", 6)
		|| !ft_strncmp(cmd, "echo", 5) || !ft_strncmp(cmd, "pwd", 4)
		|| !ft_strncmp(cmd, "env", 4) || !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "exit", 5))
	{
		if (flag == 1)
			choose_build_in_function(env, s, utils, 0);
		return (1);
	}
	else
		return (0);
}

int	child_minishell(t_e *env)
{
	char		**data;
	static char	*path[] = {"minishell", NULL};
	t_e			*pwd;
	char		*min;

	data = build_envp(env);
	pwd = find_env_data(env, "PWD=");
	if (!pwd)
		return (1);
	min = ft_strjoin(pwd->content + 4, "/minishell");
	if (execve(min, path, data))
	{
		free(data);
		exit (1);
	}
	return (0);
}

void	made_new_minishell(t_e *env)
{
	int			pid;
	int			sig;

	pid = fork();
	if (pid == 0)
	{
		if (child_minishell(env))
			return ;
	}
	else
		waitpid(pid, &sig, 0);
	g_return_code = WEXITSTATUS(sig);
	if (!g_return_code && WIFSIGNALED(sig))
		g_return_code = 128 + WTERMSIG(sig);
}
