/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmdstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 13:30:26 by senglish          #+#    #+#             */
/*   Updated: 2021/12/02 20:59:25 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_split(char **dbl_arr)
{
	int	cnt;

	cnt = 0;
	while (dbl_arr[cnt])
	{
		free(dbl_arr[cnt]);
		dbl_arr[cnt++] = NULL;
	}
	free(dbl_arr);
	dbl_arr = NULL;
}

char	*check_commands(t_fd *descriptor, char *cmd)
{
	char	*add_dir;
	int		cnt;
	int		excv;

	excv = 0;
	cnt = 0;
	while (descriptor->path[cnt])
	{
		add_dir = ft_strjoin(descriptor->path[cnt++], cmd);
		if (access(add_dir, 0) == 0)
		{
			free_split(descriptor->path);
			free(cmd);
			cmd = NULL;
			return (add_dir);
		}
		free(add_dir);
		add_dir = NULL;
	}
	free_split(descriptor->path);
	free(cmd);
	cmd = NULL;
	error(3, descriptor->cmd[0]);
	return (NULL);
}

static char	*add_slash(t_fd *descriptor)
{
	char	**slash;
	char	*add_slsh;
	int		cnt;

	cnt = 0;
	slash = NULL;
	if (access(descriptor->cmd[0], 0) < 0)
		error(1, descriptor->cmd[0]);
	slash = ft_split(descriptor->cmd[0], '/');
	if (!slash)
		error_with_std_function(12);
	while (slash[cnt])
		cnt++;
	add_slsh = ft_strjoin("/", slash[cnt - 1]);
	if (!add_slsh)
		error_with_std_function(13);
	free(slash);
	slash = NULL;
	return (add_slsh);
}

char	*no_path(t_fd *descriptor, char **cmd)
{
	if (access(cmd[0], 0) < 0)
		return (cmd[0]);
	descriptor->path = ft_split(cmd[0], 58);
	descriptor->cmd = cmd;
	return (cmd[0]);
}

char	*add_dir(t_fd *descriptor, char **cmd, char **envp)
{
	const char	str[] = "PATH=";
	char		*dir;
	char		*path;
	char		*add_slsh;
	int			cnt;

	add_slsh = NULL;
	path = NULL;
	dir = NULL;
	cnt = 0;
	while (envp && envp[cnt] && ft_strncmp(str, envp[cnt], ft_strlen(str)))
		cnt++;
	if (!envp[cnt])
		return (no_path(descriptor, cmd));
	path = ft_strchr(envp[cnt], '=') + 1;
	descriptor->path = ft_split(path, 58);
	descriptor->cmd = cmd;
	if (ft_strchr(descriptor->cmd[0], '/'))
		add_slsh = add_slash(descriptor);
	else
		add_slsh = ft_strjoin("/", descriptor->cmd[0]);
	if (!add_slsh)
		error_with_std_function(14);
	dir = check_commands(descriptor, add_slsh);
	if (!dir)
		error_with_std_function(15);
	return (dir);
}
