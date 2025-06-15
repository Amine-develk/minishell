/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnahli <mnahli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:40:25 by mnahli            #+#    #+#             */
/*   Updated: 2025/06/14 13:43:19 by mnahli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exec_cmd(t_fd *fd, t_cmd *cmds, t_env **env, char **envp)
{
	cmds->pid = fork();
	if (cmds->pid < 0)
	{
		perror("minishell: fork");
		return (close_fds(fd), FAILURE);
	}
	if (cmds->pid == 0)
		child_process(cmds, fd, env, envp);
	else
	{
		close(fd->pipefd[1]);
		if (fd->fdin != STDIN_FILENO)
			close(fd->fdin);
		if (!cmds->next || cmds->next->infile || cmds->next->heredoc)
			close(fd->pipefd[0]);
		else
			fd->fdin = fd->pipefd[0];
	}
	return (SUCCESS);
}

int	cmd_handler(t_cmd *current, t_env **env, int *prv_pipe, t_fd *fd)
{
	int	i;

	i = 0;
	if (current->pipe)
		*prv_pipe = 1;
	if (current->heredoc && current->heredoc[i])
	{
		while (current->heredoc[i]) // explanation: https://chatgpt.com/c/683454b8-e3e0-800e-9a6e-f8ea7f410ff2
		{
			if (ft_heredoc(current->heredoc[i], *env) == FAILURE)
				return (setup_signals(), g_exit_code = FAILURE, FAILURE);
			i++;
		}
		setup_signals();
	}
	g_exit_code = open_redir(current, fd);
	if (!current->args)
		close_fds(fd);
	return (SUCCESS);
}

void	exec(t_cmd **cmd, t_env **env, char **envp, t_fd *fd)
{
	t_cmd	*current;
	int		prv_pipe;

	/*prv_pipe is a flag (0 or 1) to track if the previous command used a pipe. It's needed to properly set up stdin for the current command.*/
	current = *cmd;
	prv_pipe = 0;
	// resolve cmd paths
	resolve_cmd_path(envp, *cmd);
	// iterate over each cmd
	while (current)
	{
		// prepare the cmd
		if (cmd_handler(current, env, &prv_pipe, fd) == FAILURE)
			break ;
		// if it's a builtin (like cd, export, unset,...)
		if (current->args && is_builtin(current->args[0]) && !current->pipe && !prv_pipe)
			exec_bltin(current, env, fd);
		// Handle exit specially
		else if (current->args && !ft_strcmp(current->args[0], "exit"))
		{
			if (!current->pipe && !prv_pipe)
				ft_exit(current->args, cmd, env, fd);
		}
		// Execute external cmd
		else if (current->args && current->args[0])
			if (ft_exec_cmd(fd, current, env, envp) == FAILURE)
				break ;
		// Go to the next cmd
	}
	// wait for all children
	// reset signal handling
}
