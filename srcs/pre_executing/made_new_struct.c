/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   made_new_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:08:19 by myael             #+#    #+#             */
/*   Updated: 2021/11/28 15:37:07 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*skip_error_process(t_list *list, t_data *s)
{
	s->command = NULL;
	while (list && !data_is_pipe(list))
		list = list->next;
	return (list);
}

t_list	*skip_pipe_data(t_list *list, int amount, t_data *s)
{
	s->command = NULL;
	if (amount == -1)
		return (NULL);
	else if (amount == -2)
	{
		while (list && !data_is_pipe(list))
			list = list->next;
		return (list);
	}
	return (list);
}

t_list	*made_massive_command(t_list *list, int amount, t_data *s)
{
	char	**command;
	int		a;

	a = 0;
	command = malloc(sizeof(char *) * (amount + 1));
	while (list && !data_is_pipe(list))
	{
		if (list && data_redirect_and_heredoc(list))
			list = list->next->next;
		else
		{
			if ((list->flag_dollar_expanded && *(list->content))
				|| !(list->flag_dollar_expanded))
			{
				command[a] = ft_strdup(list->content);
				a++;
			}
			list = list->next;
		}
	}
	command[a] = NULL;
	s->command = command;
	return (list);
}

void	add_command_and_args(t_list *list, t_data *s)
{
	int	amount;

	while (list)
	{
		if (s->err == 1)
			list = skip_error_process(list, s);
		else
		{
			amount = count_amount_of_args(list);
			if (amount == -1 || amount == -2)
				list = skip_pipe_data(list, amount, s);
			else
				list = made_massive_command(list, amount, s);
		}
		if (list && data_is_pipe(list))
		{
			s = s->next;
			list = list->next;
		}
	}
}

void	ft_made_new_struct(t_list *list, t_data *s)
{
	start_heredoc(list, s);
	made_redirects(list, s);
	add_command_and_args(list, s);
}
