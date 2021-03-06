/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:59:57 by myael             #+#    #+#             */
/*   Updated: 2021/12/02 21:00:52 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export_data(char **data, t_data *s)
{
	int		a;
	int		len;
	char	*key;

	a = 0;
	while (data[a])
	{
		ft_putstr_fd("declare -x ", s->out);
		len = ft_strchr_len(data[a], '=');
		if (len == -1)
			ft_putendl_fd(data[a], s->out);
		else
		{
			key = ft_substr(data[a], 0, len + 1);
			ft_putstr_fd(key, s->out);
			free(key);
			ft_putstr_fd("\"", s->out);
			ft_putstr_fd(data[a] + len + 1, s->out);
			ft_putendl_fd("\"", s->out);
		}
		a++;
	}
}

void	sort_export_data(t_e *env, t_data *s)
{
	char	**data;
	char	*temp;
	int		a;
	int		b;

	data = build_envp(env);
	a = 0;
	while (data[a])
	{
		b = 0;
		while (data[b])
		{
			if (ft_strncmp(data[b], data[b + 1], ft_strlen(data[b])) > 0)
			{
				temp = data[b];
				data[b] = data[b + 1];
				data[b + 1] = temp;
			}
			b++;
		}
		a++;
	}
	print_export_data(data, s);
	free(data);
}

int	check_for_error_data(char *data, char c)
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (!(ft_isalpha(data[i]) || data[i] == '_' ) || (data[i] == '='))
			break ;
		i++;
	}
	if (data[i] && data[i] != '=')
	{
		if (c == 'e')
			ft_putstr_fd("minishell: export: `", 2);
		else if (c == 'u')
			ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(data, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		g_return_code = 1;
		return (1);
	}
	return (0);
}

void	add_new_data(t_e **env, char *command)
{
	t_e	*list;

	list = find_env_data(*env, command);
	if (list)
	{
		if (ft_strchr(command, '='))
			change_data_in_list(list, command);
	}
	else
		ft_envadd_back(env, ft_envnew(ft_strdup(command)));
}

void	export_build_in(t_e **env, t_data *s)
{
	int	a;

	a = 1;
	if (!s->command[1])
		sort_export_data(*env, s);
	else
	{
		while (s->command[a])
		{
			if (check_for_error_data(s->command[a], 'e'))
				;
			else
			{
				add_new_data(env, s->command[a]);
				g_return_code = 0;
			}
			a++;
		}
	}
}
