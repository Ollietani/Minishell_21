/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:58:17 by myael             #+#    #+#             */
/*   Updated: 2021/11/24 11:13:09 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_there_is_error(t_list *data)
{
	char	*copy;
	int		len;

	copy = data->content;
	len = ft_strlen(copy);
	if (len > 2)
	{
		printf("minishell: syntax error - unexpected token\n");
		return (1);
	}
	else if (len == 2)
	{
		if (!ft_strncmp(copy, "||", 3))
			return (print_error('|'));
		else if (!ft_strncmp(copy, "><", 3))
			return (print_error('<'));
		else if (!ft_strncmp(copy, "<>", 3))
			return (print_error('n'));
	}
	return (0);
}

int	check_only_redirect_pipe(t_list *data)
{
	char	*copy;
	int		len;
	int		i;

	i = 0;
	copy = data->content;
	len = ft_strlen(copy);
	if (data->flag_in_quotes == 1)
		return (0);
	while (copy[i] && (copy[i] == '|' || copy[i] == '>' || copy[i] == '<'))
		i++;
	if (len == i)
		return (1);
	return (0);
}

int	check_syntax_errors(t_list *data)
{
	while (data)
	{
		if (check_only_redirect_pipe(data))
		{
			if (if_there_is_error(data))
				return (1);
		}
		data = data->next;
	}
	return (0);
}

int	data_dollar_num(t_list *data, int i, char *str)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(str, 0, i - 1);
	tmp2 = ft_strdup(str + i + 1);
	free(data->content);
	data->content = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	return (i);
}

int	data_dollar_question(t_list *data, int i, char *str)
{
	char	*tmp;
	char	*tmp2;
	char	*ret_value;
	int		len;

	tmp = ft_substr(str, 0, i - 1);
	ret_value = ft_itoa(g_return_code);
	len = ft_strlen(ret_value);
	tmp2 = ft_strjoin(tmp, ret_value);
	free(tmp);
	free(ret_value);
	tmp = ft_strdup(str + i + 1);
	free(data->content);
	data->content = ft_strjoin(tmp2, tmp);
	free(tmp);
	free(tmp2);
	return (i + len - 1);
}
