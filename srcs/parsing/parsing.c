/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:38:48 by myael             #+#    #+#             */
/*   Updated: 2021/11/24 10:59:26 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char *cmd, int i, char quote)
{
	int	copy;

	copy = i;
	while (cmd[++i])
	{
		if (cmd[i] == quote)
			return (i);
	}
	return (copy);
}

char	*split_special_symbols(t_list **data, char *cmd, int i)
{
	int		i_copy;

	i_copy = i;
	if (i > 0)
		ft_lstadd_back(data, ft_lstnew(ft_substr(cmd, 0, i)));
	while (cmd[i] && (cmd[i] == '|' || cmd[i] == '<' || cmd[i] == '>'))
		i++;
	ft_lstadd_back(data, ft_lstnew(ft_substr(cmd, i_copy, i - i_copy)));
	if (!cmd[i])
		return (NULL);
	return (cmd + i);
}

char	*add_data_to_list(char *cmd, int i, t_list **data)
{	
	int		i_copy;
	char	*new;

	i_copy = i;
	if (!cmd[i])
	{
		ft_lstadd_back(data, ft_lstnew(ft_strdup(cmd)));
		return (NULL);
	}
	if (cmd[i] == '|' || cmd[i] == '<' || cmd[i] == '>')
	{
		new = split_special_symbols(data, cmd, i);
		while (new && *new == ' ')
			new++;
		return (new);
	}
	while (cmd[i] && cmd[i] == ' ')
		i++;
	ft_lstadd_back(data, ft_lstnew(ft_substr(cmd, 0, i_copy)));
	return (cmd + i);
}

int	check_char_type(char y)
{
	if (y == ' ' || y == '|' || y == '<' || y == '>')
		return (1);
	else
		return (0);
}

void	split_commands(char *cmd, t_list **data)
{
	int		i;
	char	*copy_to_free;

	i = 0;
	cmd = ft_strtrim(cmd, " \t\v\b\r");
	copy_to_free = cmd;
	if (!*cmd)
	{
		free(cmd);
		return ;
	}
	while (cmd && cmd[i])
	{
		while (cmd[i] && !(check_char_type(cmd[i])))
		{
			if (cmd[i] == '\'')
				i = check_quote(cmd, i, '\'');
			else if (cmd[i] == '\"')
				i = check_quote(cmd, i, '\"');
			i++;
		}
		cmd = add_data_to_list(cmd, i, data);
		i = 0;
	}
	free(copy_to_free);
}
