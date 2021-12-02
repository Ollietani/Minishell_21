/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 13:30:21 by senglish          #+#    #+#             */
/*   Updated: 2021/12/02 20:58:02 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	multiple_commands(t_e **env, t_data *s, t_utils *utils, t_fd *pipex)
{
	int		count;

	count_pipes(pipex, utils);
	child_process(pipex, s, utils, env);
	close_fd(pipex->fds);
	close_inout(s);
	count = -1;
	signal_for_main_with_fork();
	while (pipex->size-- > 0)
		waitpid_and_return(pipex, ++count);
	count = -1;
	while (pipex->fds[++count])
		free(pipex->fds[count]);
	free(pipex->fds);
}

void	check_fds(t_data *s)
{
	if (s->in < 0)
		error(2, NULL);
	else if (s->in > 0)
	{
		if (dup2(s->in, STDIN_FILENO) < 0)
			error(2, NULL);
		close(s->in);
	}
	if (s->out > 1)
	{
		if (dup2(s->out, STDOUT_FILENO) < 0)
			error(2, NULL);
		close(s->out);
	}
}

void	waitpid_and_return(t_fd *pipex, int count)
{
	int	sig;

	waitpid(pipex->pids[count], &sig, 0);
	g_return_code = WEXITSTATUS(sig);
	if (!g_return_code && WIFSIGNALED(sig))
		g_return_code = 128 + WTERMSIG(sig);
}

void	single_command(t_e **env, t_data *s, t_utils *utils, t_fd *pipex)
{
	char	**envp;

	if (check_if_build_in_or_null(env, s, utils, 1))
		return ;
	pipex->pids[0] = fork();
	if (pipex->pids[0] < 0)
		ft_putstr_fd("Can't make a fork\n", 2);
	if (pipex->pids[0] == 0)
	{
		envp = build_envp(*env);
		child_signals();
		if_no_first_command(s);
		pipex->com[0] = add_dir(pipex, s->command, envp);
		check_fds(s);
		if (execve(pipex->com[0], pipex->cmd, envp) < 0)
			error(2, pipex->com[0]);
	}
	close_inout(s);
	signal_for_main_with_fork();
	waitpid_and_return(pipex, 0);
}

void	pipex(t_data *s, t_utils *utils, t_e **env)
{
	t_fd	pipex;

	ignore_signals();
	if (s->command && s->command[0]
		&& (!ft_strncmp(s->command[0], "minishell", 10)
			|| !ft_strncmp(s->command[0], "./minishell", 12))
		&& utils->amount == 1)
	{
		made_new_minishell(*env);
		return ;
	}
	memory_alloc(&pipex, utils);
	if (utils->amount == 1)
		single_command(env, s, utils, &pipex);
	else
		multiple_commands(env, s, utils, &pipex);
	free(pipex.com);
	free(pipex.pids);
}
