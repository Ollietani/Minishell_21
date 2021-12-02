/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:07:59 by myael             #+#    #+#             */
/*   Updated: 2021/11/24 11:08:01 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_in_env(char *var, t_e *env)
{
	int		len;
	char	*new_data;

	len = ft_strlen(var);
	while (env)
	{
		if (!ft_strncmp(var, env->content, len) && env->content[len] == '=')
		{
			new_data = ft_memchr(env->content, '=', ft_strlen(env->content));
			new_data++;
			return (ft_strdup(new_data));
		}
		env = env->next;
	}
	return (NULL);
}

int	check_path(int i, char *str)
{
	while (str[i] && (ft_isalnum((int)str[i]) || str[i] == '_'))
		i++;
	return (i);
}

int	data_change_path(t_list *data, int i, char *str, t_e *env)
{
	int		start;
	char	*tmp2;
	char	*new;
	char	*tmp;
	int		len;

	start = i;
	i = check_path(i, str);
	if (start == i)
		return (i);
	tmp = ft_substr(str, start, i - start);
	new = check_in_env(tmp, env);
	free(tmp);
	tmp = ft_substr(str, 0, start - 1);
	len = ft_strlen(new);
	tmp2 = ft_strjoin(tmp, new);
	if (new)
		free(new);
	free(tmp);
	free(data->content);
	tmp = ft_strdup(str + i);
	data->content = ft_strjoin(tmp2, tmp);
	free(tmp);
	free(tmp2);
	return (start + len - 1);
}

int	check_path_data(t_list *data, int i, char *str, t_e *env)
{
	if (data->flag_not_change_dollars == 1)
		return (check_path(i, str));
	if (str[i] && str[i] == '?')
	{
		i = data_dollar_question(data, i--, str);
		return (i);
	}
	if (str[i] && ft_isdigit((int)str[i]))
	{
		i = data_dollar_num(data, i--, str);
		return (i);
	}
	if (str[i] && (ft_isalnum((int)str[i]) || str[i] == '_'))
		i = data_change_path(data, i, str, env);
	return (i);
}

int	delete_double_quotes(t_list *data, int start, char *str, t_e *env)
{
	int	i;

	i = start + 1;
	while (str[i] && str[i] != '\"')
		i++;
	if (!str[i])
		return (start + 1);
	i = start + 1;
	while (str[i] && str[i] != '\"')
	{
		if (str[i] == '$')
		{
			i = check_path_data(data, ++i, str, env);
			str = data->content;
		}
		if (str[i] != '\"')
			i++;
	}
	i = change_double(data, start, str, i);
	return (i + 1);
}
