/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 13:30:03 by senglish          #+#    #+#             */
/*   Updated: 2021/12/02 20:07:40 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_process(t_data *s, t_utils *utils, t_fd *pipex)
{
	if (pipex->size == 0)
		first_child(s, pipex);
	else if (pipex->size != utils->amount - 1)
		middle_child(s, pipex);
	else
		last_child(s, pipex);
}

void	last_child(t_data *s, t_fd *pipex)
{
	if (s->in > 0)
	{
		if (dup2(s->in, STDIN_FILENO) < 0)
			error(2, NULL);
		close(s->in);
	}
	else if (dup2(pipex->fds[pipex->size - 1][0], STDIN_FILENO) < 0)
		error(2, NULL);
	if (s->out > 1)
	{
		if (dup2(s->out, STDOUT_FILENO) < 0)
			error(2, NULL);
		close(s->out);
	}
}

void	first_child(t_data *s, t_fd *pipex)
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
	else if (dup2(pipex->fds[pipex->size][1], STDOUT_FILENO) < 0)
		error(2, NULL);
}

void	middle_child(t_data *s, t_fd *pipex)
{
	if (s->in > 0)
	{
		if (dup2(s->in, STDIN_FILENO) < 0)
			error(2, NULL);
		close(s->in);
	}
	else if (dup2(pipex->fds[pipex->size - 1][0], STDIN_FILENO) < 0)
		error(2, NULL);
	if (s->out > 1)
	{
		if (dup2(s->out, STDOUT_FILENO) < 0)
			error(2, NULL);
		close(s->out);
	}
	else if (dup2(pipex->fds[pipex->size][1], STDOUT_FILENO) < 0)
		error(2, NULL);
}
