/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:12:03 by myael             #+#    #+#             */
/*   Updated: 2021/11/24 11:12:36 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(char type)
{
	if (type == '|')
		printf("minishell: syntax error near unexpected token `|'\n");
	else if (type == '<')
		printf("minishell: syntax error near unexpected token `<'\n");
	else if (type == 'n')
		printf("minishell: syntax error near unexpected token `newline'\n");
	return (1);
}

int	data_pipe_or_redirect(t_list *data)
{
	char	*copy;

	copy = data->content;
	if (data->flag_in_quotes == 1)
		return (0);
	if (!ft_strncmp(copy, ">", 2) || !ft_strncmp(copy, "<", 2)
		|| !ft_strncmp(copy, ">>", 3) || !ft_strncmp(copy, "<<", 3)
		|| !ft_strncmp(copy, "|", 2))
		return (1);
	return (0);
}

int	both_data_spec_symbols(char *copy, char *next)
{
	if ((!ft_strncmp(copy, "|", 2) && !ft_strncmp(next, "|", 2)) \
		|| ((!ft_strncmp(copy, ">", 2) || !ft_strncmp(copy, "<", 2) \
		|| !ft_strncmp(copy, ">>", 3) || !ft_strncmp(copy, "<<", 3))
			&& !ft_strncmp(next, "|", 2)))
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	if ((!ft_strncmp(copy, ">", 2) || !ft_strncmp(copy, "<", 2) \
			|| !ft_strncmp(copy, ">>", 3) || !ft_strncmp(copy, "<<", 3)) \
			&& (!ft_strncmp(next, ">", 2) || !ft_strncmp(next, "<", 2) \
			|| !ft_strncmp(next, ">>", 3) || !ft_strncmp(next, "<<", 3)))
	{
		printf("minishell: syntax error near unexpected token `%s'\n", next);
		return (1);
	}
	return (0);
}

int	ft_pipe_error(t_list *data)
{
	if (!ft_strncmp(data->content, "|", 2))
		printf("minishell: syntax error near unexpected token `|'\n");
	else
		printf("minishell: syntax error near unexpected token `newline'\n");
	return (1);
}

int	check_repeated_specs(t_list *data)
{
	char	*copy;
	char	*next;

	if ((!data->next && data_pipe_or_redirect(data))
		|| (!ft_strncmp(data->content, "|", 2) && !data->flag_in_quotes))
		return (ft_pipe_error(data));
	while (data->next)
	{
		if (data->flag_in_quotes == 0 || data->next->flag_in_quotes == 0)
		{
			copy = data->content;
			next = data->next->content;
			if (both_data_spec_symbols(copy, next))
				return (1);
		}
		data = data->next;
	}
	if (data_pipe_or_redirect(data))
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}
