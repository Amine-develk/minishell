/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnahli <mnahli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:39:09 by mnahli            #+#    #+#             */
/*   Updated: 2025/06/16 09:44:19 by mnahli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_fds(t_fd *fd)
{
	if (fd->fdin >= 0)
	{
		close(fd->fdin);
		fd->fdin = -1;
	}
	if (fd->fdout >= 0)
	{
		close(fd->fdout);
		fd->fdout = -1;
	}
	if (fd->pipefd[0] >= 0)
	{
		close(fd->pipefd[0]);
		fd->pipefd[0] = -1;
	}
	if (fd->pipefd[1] >= 0)
	{
		close(fd->pipefd[1]);
		fd->pipefd[1] = -1;
	}
}

void	init_fds(t_fd *fd)
{
	fd->fdin = -1;
	fd->fdout = -1;
	fd->pipefd[0] = -1;
	fd->pipefd[1] = -1;
}
