/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:14:44 by myael             #+#    #+#             */
/*   Updated: 2021/11/25 18:46:05 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_hd(const char *str)
{
	int		num;
	char	*nmbr;
	char	*new_str;

	num = 1;
	new_str = NULL;
	nmbr = ft_itoa(num++);
	if (!nmbr)
		exit(7);
	new_str = ft_strjoin(str, nmbr);
	if (!new_str)
		exit(7);
	free(nmbr);
	while (access(new_str, 4) == 0)
	{
		free(new_str);
		nmbr = ft_itoa(num++);
		if (!nmbr)
			exit(7);
		new_str = ft_strjoin(str, nmbr);
		if (!new_str)
			exit(7);
		free(nmbr);
	}
	return (new_str);
}

void	open_file_for_heredoc(t_data *s)
{
	const char	str[] = ".file";

	if (access(str, 0) == 0)
	{
		s->hr_name = create_hd(str);
		s->in = open(s->hr_name, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (s->in < 0)
			exit(6);
	}
	else
	{
		s->in = open(str, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (s->in < 0)
			exit(6);
		s->hr_name = ft_strdup(str);
	}
}
