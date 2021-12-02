/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 21:48:01 by myael             #+#    #+#             */
/*   Updated: 2021/12/02 21:00:04 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_build_in(t_data *s, t_utils *utils)
{
	char	*buf;

	buf = get_address();
	if (!buf)
		ft_putendl_fd(utils->pwd + 4, s->out);
	else
	{
		ft_putendl_fd(buf, s->out);
		free(buf);
	}
	g_return_code = 0;
}
