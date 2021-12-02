/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:14:13 by myael             #+#    #+#             */
/*   Updated: 2021/12/02 20:57:16 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_data(t_data **s)
{
	t_data	*temp;

	if (!(*s))
		return ;
	while (*s)
	{
		if ((*s)->hr_name)
		{
			unlink((*s)->hr_name);
			(*s)->hr_name = NULL;
		}
		if ((*s)->command)
		{
			free_double_massive((*s)->command);
		}
		temp = (*s)->next;
		free(*s);
		*s = temp;
	}
	*s = NULL;
}

void	free_double_massive(char **data)
{
	int	a;

	a = 0;
	while (data[a])
	{
		free(data[a]);
		data[a] = NULL;
		a++;
	}
	free(data);
	data = NULL;
}
