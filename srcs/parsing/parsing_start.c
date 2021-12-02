/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:37:50 by myael             #+#    #+#             */
/*   Updated: 2021/12/02 18:54:01 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data_ints(t_list *data)
{
	int	counter;

	counter = 0;
	while (data)
	{
		data->flag_not_change_dollars = 0;
		data->flag_in_quotes = 0;
		data->flag_ambitious_redirect = 0;
		data->flag_dollar_expanded = 0;
		data->amb_data = NULL;
		data->num = counter;
		data = data->next;
		counter++;
	}
}

void	parse_execute_commands(char *cmd, t_utils *utils, t_e **env)
{
	t_list	*data;
	t_data	*s;

	data = NULL;
	s = NULL;
	split_commands(cmd, &data);
	if (!data)
		return ;
	init_data_ints(data);
	check_if_path_not_expand(data, *env);
	clean_commands(data, *env);
	if (check_syntax_errors(data) || check_repeated_specs(data))
	{
		g_return_code = 258;
		ft_lstclear(&data);
		return ;
	}
	if (!init_new_struct(data, &s, utils))
		return ;
	ft_made_new_struct(data, s);
	pipex(s, utils, env);
	ft_lstclear(&data);
	ft_clear_data(&s);
}
