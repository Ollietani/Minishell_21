/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:05:49 by myael             #+#    #+#             */
/*   Updated: 2021/11/27 21:20:19 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_data_in_list(t_e *env, char *data)
{
	free(env->content);
	env->content = ft_strdup(data);
}

static void	next_env(t_e *orig, t_e *new)
{
	t_e	*last;

	while (orig->next)
	{
		if (orig->next && !ft_strncmp(orig->next->content,
				new->content, ft_strlen(orig->next->content)))
		{
			last = orig->next;
			orig->next = orig->next->next;
			last->next = NULL;
		}
		else
			orig = orig->next;
	}
	if (last)
	{
		free(last->content);
		free(last);
	}
}

static t_e	*copy_env(t_e *env)
{
	t_e	*orig;

	orig = env->next;
	free(env->content);
	env->content = NULL;
	free(env);
	env = NULL;
	return (orig);
}

void	unset_build_in(t_data *s, t_e **env)
{
	t_e	*new;
	int	num;

	if (!(*env) || !(s->command[1]))
		return ;
	num = 0;
	g_return_code = 0;
	while (s->command[++num])
	{
		if (check_for_error_data(s->command[num], 'u'))
			;
		new = find_env_data(*env, s->command[num]);
		if (new)
		{
			if (!ft_strncmp((*env)->content, new->content,
					ft_strlen((*env)->content)))
				*env = copy_env(*env);
			else
				next_env(*env, new);
		}
	}
}
