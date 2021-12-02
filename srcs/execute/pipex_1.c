/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 22:03:16 by senglish          #+#    #+#             */
/*   Updated: 2021/12/02 20:57:48 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(t_fd *pipex, t_data *s, t_utils *utils, t_e **env)
{
	int		num;
	char	**envp;

	num = !check_if_build_in_or_null(env, s, utils, 0);
	if (!num && !s->command)
		exit (0);
	envp = build_envp(*env);
	child_signals();
	if_no_first_command(s);
	if (num)
		pipex->com[pipex->size] = add_dir(pipex, s->command, envp);
	if (num || (!num && (s->out == 1)))
		do_process(s, utils, pipex);
	close_fd(pipex->fds);
	if (!num)
		choose_build_in_function(env, s, utils, 1);
	else if (execve(pipex->com[pipex->size], pipex->cmd, envp) < 0)
		error(2, pipex->com[pipex->size]);
}

char	**build_envp(t_e *env)
{
	char	**envp;
	int		count;

	count = 0;
	envp = malloc(sizeof(char *) * (ft_envsize(env) + 1));
	if (!envp)
		error_with_std_function(10);
	while (env)
	{
		envp[count++] = env->content;
		env = env->next;
	}
	envp[count] = NULL;
	return (envp);
}

void	child_process(t_fd *pipex, t_data *s, t_utils *utils, t_e **env)
{
	pipex->size = -1;
	while (++pipex->size < utils->amount)
	{
		if (pipex->size > 0)
			s = s->next;
		pipex->pids[pipex->size] = fork();
		if (pipex->pids[pipex->size] < 0)
			error_with_std_function(21);
		if (pipex->pids[pipex->size] == 0)
			child(pipex, s, utils, env);
	}
}

void	count_pipes(t_fd *pipex, t_utils *utils)
{
	int	count;

	count = -1;
	pipex->fds = malloc(sizeof(int *) * (utils->amount));
	if (!pipex->fds)
		error_with_std_function(10);
	while (++count < utils->amount - 1)
	{
		pipex->fds[count] = malloc(sizeof(int) * 2);
		if (!pipex->fds[count])
			error_with_std_function(11);
		if (pipe(pipex->fds[count]) == -1)
		{
			while (count > -1)
			{
				free(pipex->fds[count]);
				pipex->fds[count--] = NULL;
			}
			free(pipex->fds);
			error_with_std_function(20);
		}
	}
	pipex->fds[count] = NULL;
}
