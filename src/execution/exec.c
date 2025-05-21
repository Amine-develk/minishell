/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnahli <mnahli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:40:25 by mnahli            #+#    #+#             */
/*   Updated: 2025/05/20 12:40:46 by mnahli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec(t_cmd **cmd, t_env **env, char **envp, t_fd *fd)
{
	t_cmd *current;
	int		prv_pipe;
	/*prv_pipe is a flag (0 or 1) to track if the previous command used a pipe. It's needed to properly set up stdin for the current command.*/

	current = *cmd;
	prv_pipe = 0;
	// resolve cmd paths
	resolve_cmd_path(envp, *cmd);
	// iterate over each cmd
	// prepare the cmd
	// if it's a builtin (like cd, export, unset,...)
	// Handle exit specially
	// Execute external cmd
	// Go to the next cmd
	// wait for all children
	// reset signal handling
}