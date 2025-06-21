/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:33:55 by ael-krai          #+#    #+#             */
/*   Updated: 2025/06/21 11:49:29 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_exit_code = FAILURE;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
		return ;
}

void	handle_signals(void)
{
	struct termios	terminal;

	tcgetattr(0, &terminal);
	terminal.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &terminal);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}

void	reset_terminal(void)
{
	struct termios	terminal;

	tcgetattr(0, &terminal);
	terminal.c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, &terminal);
}
