/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:44:15 by myael             #+#    #+#             */
/*   Updated: 2021/11/24 11:46:38 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(void)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_return_code = 1;
}

void	main_signals_made(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, (void *)handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	child_signals(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

void	signal_for_heredoc(void)
{
	signal(SIGINT, (void *)handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
