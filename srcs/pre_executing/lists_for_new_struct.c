/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_for_new_struct.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:15:10 by myael             #+#    #+#             */
/*   Updated: 2021/12/02 20:01:04 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*lst_new_data(int num)
{
	t_data	*new;

	new = malloc(sizeof(t_data));
	if (new == NULL)
		error_with_std_function(11);
	new->in = 0;
	new->out = 1;
	new->hr_name = NULL;
	new->num = num;
	new->command = NULL;
	new->err = 0;
	new->next = NULL;
	return (new);
}

t_data	*ft_lst_data(t_data *data)
{
	while (data->next)
		data = data->next;
	return (data);
}

void	add_back_data(t_data **s, t_data *new)
{
	t_data	*temp;

	if (!*s)
		*s = new;
	else
	{
		temp = ft_lst_data(*s);
		temp->next = new;
		new->next = NULL;
	}	
}

int	init_new_struct(t_list *data, t_data **s, t_utils *utils)
{
	int		amount;
	int		counter;

	counter = 0;
	amount = check_pipes_amount_list(data);
	utils->amount = amount;
	while (amount)
	{
		add_back_data(s, lst_new_data(counter));
		counter++;
		amount--;
	}
	return (1);
}
