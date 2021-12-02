/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_new_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:20:09 by myael             #+#    #+#             */
/*   Updated: 2021/11/27 21:14:31 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_amount_of_args(t_list *list)
{
	int	amount;

	amount = 0;
	while (list && !data_is_pipe(list))
	{
		if (list && data_redirect_and_heredoc(list))
			list = list->next->next;
		else
		{
			if ((list->flag_dollar_expanded && (*(list->content)))
				|| !(list->flag_dollar_expanded))
				amount++;
			list = list->next;
		}
	}
	if (!list && amount == 0)
		return (-1);
	if (list && amount == 0)
		return (-2);
	return (amount);
}
