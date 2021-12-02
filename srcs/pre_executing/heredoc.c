/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:11:39 by myael             #+#    #+#             */
/*   Updated: 2021/11/27 21:14:17 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_proc_heredoc(t_list *data, int save, t_data *s)
{
	char	*cmd;

	cmd = NULL;
	signal_for_heredoc();
	while (1)
	{
		cmd = readline("> ");
		if (!ft_strncmp(cmd, data->content, ft_strlen(data->content) + 1))
			break ;
		if (save == 1)
		{
			write(s->in, cmd, ft_strlen(cmd));
			write(s->in, "\n", 1);
		}
		free(cmd);
	}
	free(cmd);
	exit(0);
}

void	start_new_readline(t_list *data, int save, t_data *s)
{
	int		pid;

	if (save == 1)
		open_file_for_heredoc(s);
	pid = fork();
	if (pid == -1)
		exit(5);
	if (pid == 0)
		child_proc_heredoc(data, save, s);
	else
	{
		ignore_signals();
		wait(NULL);
	}
	close(s->in);
	s->in = open(s->hr_name, O_RDONLY, 0644);
	main_signals_made();
}

int	check_if_saved_in(t_list *data)
{
	while (data)
	{
		if ((!ft_strncmp(data->content, "<", 2) && data->flag_in_quotes == 0)
			|| (!ft_strncmp(data->content, "<<", 3) \
			&& data->flag_in_quotes == 0))
			return (0);
		if (data_is_pipe(data))
			return (1);
		data = data->next;
	}
	return (1);
}

t_list	*check_type_readline(t_list *data, t_data *s)
{
	int	a;

	a = check_if_saved_in(data);
	start_new_readline(data, a, s);
	return (data->next);
}

void	start_heredoc(t_list *list, t_data *s)
{
	while (list)
	{
		if (!ft_strncmp(list->content, "<<", 3) && list->flag_in_quotes == 0)
			list = check_type_readline(list->next, s);
		else
			list = list->next;
		if (list && data_is_pipe(list))
			s = s->next;
	}
}
