/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_redirects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:55:51 by myael             #+#    #+#             */
/*   Updated: 2021/11/28 15:36:18 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_not_last_redirect_in(t_list *list)
{
	while (list && !data_is_pipe(list))
	{
		if (data_redirect_in(list))
			return (1);
		list = list->next;
	}
	return (0);
}

int	check_if_not_last_redirect_out(t_list *list)
{
	while (list && !data_is_pipe(list))
	{
		if (data_redirect_out(list))
			return (1);
		list = list->next;
	}
	return (0);
}

t_list	*error_ambitious_data(t_list *list, t_data *s)
{
	s->err = 1;
	s->command = NULL;
	printf("minishell: %s: ambiguous redirect\n", list->amb_data);
	g_return_code = 1;
	while (list && !data_is_pipe(list))
		list = list->next;
	return (list);
}

t_list	*error_with_redirect(t_list *list, t_data *s)
{
	printf("minishell: %s: %s\n", list->next->content, strerror(errno));
	s->command = NULL;
	s->err = 1;
	while (list && !data_is_pipe(list))
		list = list->next;
	return (list);
}
