/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:54:18 by myael             #+#    #+#             */
/*   Updated: 2021/11/29 18:55:04 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	data_is_pipe(t_list *list)
{
	if ((!ft_strncmp(list->content, "|", 2) \
				&& list->flag_in_quotes == 0))
		return (1);
	else
		return (0);
}

int	check_pipes_amount_list(t_list *data)
{
	int	i;

	i = 1;
	while (data)
	{
		if (!ft_strncmp(data->content, "|", 2) && data->flag_in_quotes == 0)
			i++;
		data = data->next;
	}
	return (i);
}

int	pipe_in_data(t_list *data)
{
	while (data)
	{
		if (!ft_strncmp(data->content, "|", 2) && data->flag_in_quotes == 0)
			return (1);
		data = data->next;
	}
	return (0);
}

int	ft_find_data(t_list *data, char *cont, int len)
{
	while (data)
	{
		if (!ft_strncmp(data->content, cont, len))
			return (1);
		data = data->next;
	}
	return (0);
}

char	*ft_find_flag(t_list *data)
{
	while (data)
	{
		if (data->flag_ambitious_redirect == 1)
			return (data->amb_data);
		data = data->next;
	}
	return (NULL);
}
