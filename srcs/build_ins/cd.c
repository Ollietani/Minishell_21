/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:54:21 by myael             #+#    #+#             */
/*   Updated: 2021/12/02 21:01:03 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_chdir(char *str)
{
	int	fd;

	fd = 0;
	if (chdir((const char *)str) < 0)
	{
		fd = open(str, O_DIRECTORY);
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(str, 2);
		if (access(str, 0) < 0)
			ft_putendl_fd(": No such file or directory", 2);
		else if (fd < 0)
			ft_putendl_fd(": Permission denied", 2);
		if (fd > 0)
			close(fd);
		g_return_code = 1;
	}
}

static void	cd_back(char *pwd)
{
	char	*buf;
	char	*last;
	char	*prev;
	int		flag;

	flag = 0;
	buf = get_address();
	if (!buf && ++flag)
		buf = pwd;
	last = ft_strrchr(buf, '/');
	prev = ft_substr(buf, 0, ft_strlen(buf) - ft_strlen(last) + 1);
	if (!prev)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	do_chdir(prev);
	if (flag == 0)
		free(buf);
	free(prev);
}

char	*get_address(void)
{
	char	*buf;
	char	*copy;

	buf = malloc(sizeof(char) * 1000);
	copy = buf;
	if (!buf)
		error_with_std_function(9);
	buf = getcwd(buf, 1000);
	if (!buf)
	{
		free(copy);
		g_return_code = 2;
		return (NULL);
	}
	return (buf);
}

void	cd_build_in(char **cmd, t_e *env, char *pwd)
{
	int			a;
	const char	str[] = "HOME=";
	char		*home;

	a = 0;
	while (cmd[a])
		a++;
	while (env && (ft_strncmp(str, env->content, ft_strlen(str)) != 0))
	{
		if (env->next)
			env = env->next;
		else
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			g_return_code = 1;
			return ;
		}
	}
	home = env->content + ft_strlen(str);
	if (a == 1)
		do_chdir(home);
	else if (!ft_strncmp(cmd[1], "..", 3) && ft_strlen(cmd[1]) == 2)
		cd_back(pwd + 4);
	else
		do_chdir(cmd[1]);
}

void	change_env_pwds(t_utils *utils, t_e *env)
{
	char	*buf;
	t_e		*pwd;
	t_e		*oldpwd;

	buf = get_address();
	free(utils->old_pwd);
	utils->old_pwd = ft_strjoin("OLDPWD=", utils->pwd + 4);
	free(utils->pwd);
	utils->pwd = ft_strjoin("PWD=", buf);
	pwd = find_env_data(env, "PWD=");
	oldpwd = find_env_data(env, "OLDPWD=");
	free(oldpwd->content);
	if (!pwd)
		oldpwd->content = ft_strdup(utils->old_pwd);
	else
		oldpwd->content = ft_strjoin("OLDPWD=", pwd->content + 4);
	if (pwd)
	{	
		free(pwd->content);
		pwd->content = ft_strdup(utils->pwd);
	}
	free(buf);
}
