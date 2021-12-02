/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:48:31 by myael             #+#    #+#             */
/*   Updated: 2021/11/28 16:03:09 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_double(t_list *data, int start, char *str, int finish)
{
	char	*tmp;
	char	*tmp2;
	char	*new;

	tmp = ft_substr(str, 0, start);
	tmp2 = ft_substr(str, start + 1, finish - start - 1);
	new = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	tmp2 = ft_strdup(str + finish + 1);
	tmp = ft_strjoin(new, tmp2);
	free(tmp2);
	free(new);
	free(data->content);
	data->content = tmp;
	return (finish - 2);
}

int	change_one_quote(t_list *data, int start, char *str)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	*new;

	i = start + 1;
	while (str[i] && str[i] != '\'')
		i++;
	if (!str[i])
		return (start + 1);
	tmp = ft_substr(str, 0, start);
	tmp2 = ft_substr(str, start + 1, i - start - 1);
	new = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	tmp2 = ft_strdup(str + i + 1);
	tmp = ft_strjoin(new, tmp2);
	free(tmp2);
	free(new);
	free(data->content);
	data->content = tmp;
	return (i + 1 - 2);
}

char	*do_change_path(t_list *data, char *str, int *i, t_e *env)
{
	*i = check_path_data(data, (++(*i)), str, env);
	data->flag_dollar_expanded = 1;
	str = data->content;
	return (str);
}

void	check_arg(t_list *data, t_e *env)
{
	char	*str;
	int		i;

	i = 0;
	str = data->content;
	while (str[i])
	{
		if (!(str[i] == '\'' || str[i] == '\"' || str[i] == '$'))
			i++;
		if (str && str[i] == '\'')
		{
			i = change_one_quote(data, i, str);
			data->flag_in_quotes = 1;
			str = data->content;
		}
		if (str && str[i] == '$')
			str = do_change_path(data, str, &i, env);
		if (str && str[i] == '\"')
		{
			i = delete_double_quotes(data, i, str, env);
			data->flag_in_quotes = 1;
			str = data->content;
		}
	}
}

void	clean_commands(t_list *data, t_e *env)
{
	t_list	*copy;

	copy = data;
	while (data)
	{
		data->flag_in_quotes = 0;
		check_arg(data, env);
		data = data->next;
	}
}
