/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:11:00 by myael             #+#    #+#             */
/*   Updated: 2021/12/02 20:56:49 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_str_num(char *data)
{
	while (*data == ' ')
		data++;
	if (*data == '+' || *data == '-')
		data++;
	while (*data)
	{
		if (!ft_isdigit(*data))
			return (0);
		data++;
	}
	return (1);
}

void	error_with_std_function(int num)
{
	if (num >= 1 && num <= 15)
		ft_putstr_fd("error with malloc\n", 2);
	if (num == 20)
		ft_putstr_fd("Error: can't create a pipe\n", 2);
	if (num == 21)
		ft_putstr_fd("Can't make a fork\n", 2);
	exit (num);
}
