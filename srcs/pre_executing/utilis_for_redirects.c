/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis_for_redirects.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:16:19 by myael             #+#    #+#             */
/*   Updated: 2021/11/24 11:37:19 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	data_redirect_and_heredoc(t_list *data)
{
	char	*copy;

	copy = data->content;
	if (data->flag_in_quotes == 1)
		return (0);
	if (!ft_strncmp(copy, ">", 2) || !ft_strncmp(copy, "<", 2)
		|| !ft_strncmp(copy, ">>", 3) || !ft_strncmp(copy, "<<", 3))
		return (1);
	return (0);
}

int	data_redirect(t_list *data)
{
	char	*copy;

	copy = data->content;
	if (data->flag_in_quotes == 1)
		return (0);
	if (!ft_strncmp(copy, ">", 2) || !ft_strncmp(copy, "<", 2)
		|| !ft_strncmp(copy, ">>", 3))
		return (1);
	return (0);
}

int	data_redirect_in(t_list *data)
{
	char	*copy;

	copy = data->content;
	if (data->flag_in_quotes == 1)
		return (0);
	if (!ft_strncmp(copy, "<", 2))
		return (1);
	return (0);
}

int	data_redirect_out(t_list *data)
{
	char	*copy;

	copy = data->content;
	if (data->flag_in_quotes == 1)
		return (0);
	if (!ft_strncmp(copy, ">", 2) || !ft_strncmp(copy, ">>", 3))
		return (1);
	return (0);
}

int	ft_amount_of_args(t_list *data)
{
	int	am;

	am = 0;
	while (data && (ft_strncmp(data->content, "|", 2) \
		&& data->flag_in_quotes == 0))
	{
		if (data_redirect(data) && (ft_strncmp(data->next->content, "|", 2) \
		&& data->next->flag_in_quotes == 0))
			data = data->next->next;
		else if (data_redirect(data)
			&& (!ft_strncmp(data->next->content, "|", 2) \
			&& data->next->flag_in_quotes == 0))
			data = data->next;
		else
		{	
			am++;
			data = data->next;
		}
	}
	return (am);
}
