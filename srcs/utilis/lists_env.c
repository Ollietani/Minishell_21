/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:51:21 by myael             #+#    #+#             */
/*   Updated: 2021/12/02 19:51:19 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_envadd_back(t_e **lst, t_e *new)
{
	t_e	*temp;

	if (!(*lst))
		*lst = new;
	else
	{
		temp = ft_envlast(*lst);
		temp->next = new;
		new->next = NULL;
	}
}

t_e	*ft_envnew(char *content)
{
	t_e	*new;

	new = malloc(sizeof(t_e));
	if (!new)
		error_with_std_function(2);
	new->content = content;
	new->next = NULL;
	return (new);
}

t_e	*ft_envlast(t_e *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_clear_all(t_all *all)
{
	t_e	*temp;
	t_e	**env;

	env = &all->env;
	while (env && *env)
	{
		temp = (*env)->next;
		free((*env)->content);
		(*env)->content = NULL;
		free(*env);
		*env = NULL;
		*env = temp;
	}
	*env = NULL;
	if (*all->pwd)
	{
		free(all->pwd);
		all->pwd = NULL;
	}
	if (*all->old_pwd)
	{
		free(all->old_pwd);
		all->old_pwd = NULL;
	}
	free(all);
}

int	ft_envsize(t_e *lst)
{
	int	amount;

	amount = 0;
	while (lst)
	{
		lst = lst->next;
		amount++;
	}
	return (amount);
}
