/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   made_redirects_data.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:57:01 by myael             #+#    #+#             */
/*   Updated: 2021/11/29 18:49:47 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*open_in_files(t_list *list, t_data *s)
{
	s->in = open(list->next->content, O_RDONLY, 0644);
	if (s->in < 0)
	{
		list = error_with_redirect(list, s);
		return (list);
	}
	if (check_if_not_last_redirect_in(list->next))
		close(s->in);
	return (list->next->next);
}

t_list	*open_out_files(t_list *list, t_data *s)
{
	if (!ft_strncmp(list->content, ">", 2))
		s->out = open(list->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (!ft_strncmp(list->content, ">>", 3))
		s->out = open(list->next->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (s->out < 0)
	{
		list = error_with_redirect(list, s);
		return (list);
	}
	if (check_if_not_last_redirect_out(list->next))
		close(s->out);
	return (list->next->next);
}

t_list	*open_redirect(t_list *list, t_data *s)
{
	if (list->flag_ambitious_redirect == 1)
	{
		list = error_ambitious_data(list, s);
		return (list);
	}
	if (data_redirect_in(list))
		list = open_in_files(list, s);
	else if (data_redirect_out(list))
		list = open_out_files(list, s);
	return (list);
}

void	made_redirects(t_list *list, t_data *s)
{
	while (list)
	{
		if (data_redirect(list))
			list = open_redirect(list, s);
		else
			list = list->next;
		if (list && data_is_pipe(list))
		{
			s = s->next;
			list = list->next;
		}
	}
}
