/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:46:03 by myael             #+#    #+#             */
/*   Updated: 2021/11/24 11:47:23 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint_fork(void)
{
	write(2, "\n", 1);
}

void	handle_sigquit_fork(void)
{
	write(2, "Quit: 3\n", 9);
}

void	signal_for_main_with_fork(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, (void *)handle_sigint_fork);
	signal(SIGQUIT, (void *)handle_sigquit_fork);
}
