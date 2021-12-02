/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 22:03:32 by senglish          #+#    #+#             */
/*   Updated: 2021/12/02 20:57:37 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_no_first_command(t_data *s)
{
	if (!ft_strlen(s->command[0]))
	{
		close_inout(s);
		error(3, s->command[0]);
	}
}

void	close_fd(int **fds)
{
	int	cnt1;
	int	cnt2;

	cnt1 = -1;
	while (fds[++cnt1])
	{
		cnt2 = -1;
		while (fds[cnt1][++cnt2])
			close(fds[cnt1][cnt2]);
	}
}

void	close_inout(t_data *s)
{
	while (s)
	{
		if (s->in > 0)
			close(s->in);
		if (s->out > 1)
			close(s->out);
		s = s->next;
	}
}

void	memory_alloc(t_fd *pipex, t_utils *utils)
{
	pipex->pids = malloc(sizeof(int) * utils->amount + 1);
	if (!pipex->pids)
		error(2, NULL);
	pipex->pids[utils->amount] = '\0';
	pipex->com = malloc(sizeof(char *) * utils->amount + 1);
	if (!pipex->com)
		error(2, NULL);
	pipex->com[utils->amount] = "\0";
}
