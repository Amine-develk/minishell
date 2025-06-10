/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnahli <mnahli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:55:44 by mnahli            #+#    #+#             */
/*   Updated: 2025/05/29 12:58:25 by mnahli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		exit(1);
	}
	else if (sig == SIGQUIT)
		return ;
}