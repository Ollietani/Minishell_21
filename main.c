/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:36:12 by myael             #+#    #+#             */
/*   Updated: 2021/12/02 21:01:42 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_pwd_data(t_utils *utils, t_e *env)
{
	t_e	*pwd;

	pwd = find_env_data(env, "PWD=");
	if (pwd)
		utils->pwd = ft_strdup(pwd->content + 4);
	pwd = find_env_data(env, "OLDPWD=");
	if (pwd)
		utils->old_pwd = ft_strdup(pwd->content + 7);
}

static void	main_do(t_utils *utils, t_e **env)
{
	char	*cmd;

	cmd = readline("minishell$ ");
	if (!cmd)
	{
		ft_putendl_fd("exit", 1);
		exit_minishell();
	}
	if (ft_strlen(cmd) > 0)
		add_history(cmd);
	if (*cmd)
		parse_execute_commands(cmd, utils, env);
	free(cmd);
}

int	main(int argc, char **argv, char **envp)
{
	t_utils	*utils;
	t_e		*env;

	(void)argc;
	(void)argv;
	utils = malloc(sizeof(t_utils));
	if (!utils)
		error_with_std_function(1);
	env = add_env(envp);
	change_env_data(&env);
	add_pwd_data(utils, env);
	while (1)
	{
		main_signals_made();
		main_do(utils, &env);
	}
	return (0);
}
