/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:46:09 by myael             #+#    #+#             */
/*   Updated: 2021/11/24 10:46:21 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_data(t_list **data, t_e *env)
{
	char	*data_n;

	data_n = (*data)->next->content;
	data_n = check_in_env(data_n + 1, env);
	if (!data_n)
	{
		(*data)->amb_data = ft_strdup((*data)->next->content);
		(*data)->flag_ambitious_redirect = 1;
	}
	else
		free(data_n);
}

void	check_if_change(t_list **data, t_e *env)
{
	char	*data_c;
	char	*data_n;

	data_c = (*data)->content;
	if ((*data)->next)
	{
		data_n = (*data)->next->content;
		if ((!ft_strncmp(data_c, ">", 2) || !ft_strncmp(data_c, "<", 2) \
			|| !ft_strncmp(data_c, ">>", 3)) && data_n[0] == '$')
		{
			if (ft_strlen(data_n) > 1 && check_path(0, data_n + 1) > 0)
				check_data(data, env);
		}
	}
	if (!ft_strncmp(data_c, "<<", 3))
	{
		if (!(*data)->next)
			return ;
		(*data)->next->flag_not_change_dollars = 1;
	}
}

void	check_if_path_not_expand(t_list *data, t_e *env)
{
	while (data)
	{
		check_if_change(&data, env);
		data = data->next;
	}
}
