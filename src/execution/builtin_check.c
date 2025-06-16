/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnahli <mnahli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:49:45 by mnahli            #+#    #+#             */
/*   Updated: 2025/06/16 09:46:09 by mnahli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *command)
{
	if (!command || !command[0])
		return (0);
	return (!ft_strcmp(command, "cd") || !ft_strcmp(command, "echo")
		|| !ft_strcmp(command, "pwd") || !ft_strcmp(command, "env")
		|| !ft_strcmp(command, "export") || !ft_strcmp(command, "unset"));
}

void	exec_builtin(char **args, t_env **env)
{
	if (!ft_strcmp(args[0], "echo"))
		g_exit_code = ft_echo(args);
	if (!ft_strcmp(args[0], "cd"))
		g_exit_code = ft_cd(args, env);
	if (!ft_strcmp(args[0], "pwd"))
		g_exit_code = ft_pwd();
	if (!ft_strcmp(args[0], "env"))
		g_exit_code = ft_env(*env);
	if (!ft_strcmp(args[0], "export"))
		g_exit_code = ft_export(args, env);
	if (!ft_strcmp(args[0], "unset"))
		g_exit_code = ft_unset(args, env);
}

int	exec_bltin(t_cmd *current, t_env **env, t_fd *fd)
{
	int	stdin_copy;
	int	stdout_copy;

	if (current->infile && fd->fdin == -1)
		return (g_exit_code = FAILURE, FAILURE);
	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	if (current->outfile)
		if (dup_stdout(fd, fd->fdout) == FAILURE)
			return (g_exit_code = FAILURE, FAILURE);
	exec_builtin(current->args, env);
	if (dup_stdin(fd, stdin_copy) == FAILURE)
		return (g_exit_code = FAILURE, FAILURE);
	if (dup_stdout(fd, stdout_copy) == FAILURE)
		return (g_exit_code = FAILURE, FAILURE);
	close(stdin_copy);
	close(stdout_copy);
	if (fd->fdin != STDIN_FILENO)
		close(fd->fdin);
	if (fd->fdout != STDOUT_FILENO)
		close(fd->fdout);
	return (SUCCESS);
}
