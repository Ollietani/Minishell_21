/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 21:15:14 by myael             #+#    #+#             */
/*   Updated: 2021/11/27 21:21:20 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	for_echo(char **command, int a, int *flag)
{
	if (command[a] && !ft_strncmp(command[a], "-n", 3))
	{
		*flag = 1;
		a++;
	}
	while (command[a] && !ft_strncmp(command[a], "-n", 3))
		a++;
	return (a);
}

void	echo_build_in(t_data *s)
{
	char	**command;
	int		a;
	int		flag;

	flag = 0;
	command = s->command;
	a = 1;
	if (!command[a])
		write(s->out, "\n", 1);
	else
	{	
		a = for_echo(command, a, &flag);
		while (command[a] && command[a + 1])
		{
			ft_putstr_fd(command[a], s->out);
			write(s->out, " ", 1);
			a++;
		}
		ft_putstr_fd(command[a], s->out);
		if (flag == 0)
			write(s->out, "\n", 1);
	}
	g_return_code = 0;
}
