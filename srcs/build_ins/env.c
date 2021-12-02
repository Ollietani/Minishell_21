/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 21:59:13 by myael             #+#    #+#             */
/*   Updated: 2021/11/27 21:21:10 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_build_in(t_e *env, t_data *s)
{
	while (env)
	{
		if (ft_strrchr(env->content, '='))
		{
			ft_putstr_fd(env->content, s->out);
			write(s->out, "\n", 1);
		}
		env = env->next;
	}
	g_return_code = 0;
}

void	change_env_data(t_e **env)
{
	t_e		*data;
	int		num;
	char	*str_num;

	data = find_env_data(*env, "SHLVL=");
	if (!data)
		ft_envadd_back(env, ft_envnew("SHLVL=1"));
	else
	{
		num = ft_atoi(data->content + 6);
		num++;
		str_num = ft_itoa(num);
		free(data->content);
		data->content = ft_strjoin("SHLVL=", str_num);
		free(str_num);
	}
	data = find_env_data(*env, "OLDPWD=");
	if (data)
	{
		free(data->content);
		data->content = ft_strdup("OLDPWD");
	}
}

t_e	*add_env(char **envp)
{
	t_e		*env;
	char	*new_data;

	env = NULL;
	while (*envp)
	{
		new_data = ft_strdup(*envp);
		ft_envadd_back(&env, ft_envnew(new_data));
		envp++;
	}
	return (env);
}

t_e	*find_env_data(t_e *env, char *data)
{
	int	len;

	if (ft_strchr(data, '='))
		len = ft_strchr_len(data, '=');
	else
		len = ft_strlen(data);
	while (env)
	{
		if (!ft_strncmp(data, env->content, len)
			&& (env->content[len] == '=' || !env->content[len]))
			return (env);
		env = env->next;
	}
	return (NULL);
}
