/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnahli <mnahli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:35:40 by mnahli            #+#    #+#             */
/*   Updated: 2025/06/16 09:53:20 by mnahli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	var_in_line(char *delimiter, char *line)
{
	int i;
	int dlm_len;

	if (!delimiter || !line)
		return (0);
	dlm_len = ft_strlen(delimiter);
	if (dlm_len == 0 || dlm_len == 1)
		return (0);
	if ((delimiter[0] == '\'' && delimiter[dlm_len - 1] == '\'')
		|| (delimiter[0] == '\"' && delimiter[dlm_len - 1] == '\"'))
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] && line[i + 1] != ' ' && line[i
			+ 1] != '\n')
			return (1);
		i++;
	}
	return (0);
}

void	error_path(char *msg, char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
}

int	check_is_dir(char *cmd)
{
	DIR	*dir;

	dir = opendir(cmd);
	if (ft_strcmp(cmd, ".") == 0)
	{
		ft_putstr_fd("minishell: .: filename argument required\n",
			STDERR_FILENO);
		ft_putstr_fd(".: usage: . filename [arguments]\n", STDERR_FILENO);
		return (closedir(dir), exit(2), 1);
	}
	else if (dir && (ft_strchr(cmd, '/')))
		return (closedir(dir), error_path(": is a directory\n", cmd), exit(126),
			1);
	else if (dir)
		closedir(dir);
	else if ((ft_strchr(cmd, '/')) && access(cmd, F_OK) == -1)
	{
		error_path(": No such file or directory\n", cmd);
		return (exit(127), 1);
	}
	else if ((ft_strchr(cmd, '/')) && access(cmd, X_OK) == -1)
		return (error_path(": Permission denied\n", cmd), exit(126), 1);
	return (0);
}

void	exit_func(t_fd *fd, int status)
{
	close_fds(fd);
	g_exit_code = status;
	exit(g_exit_code);
}

void	cmd_files_handler(t_cmd *cmd, t_fd *fd)
{
	if (fd->fdin >= 0)
	{
		if (dup_stdin(fd, fd->fdin) == FAILURE)
			exit_func(fd, FAILURE);
	}
	if ((cmd->heredoc || cmd->infile) && fd->fdin == -1)
		exit_func(fd, FAILURE);
	if (cmd->outfile)
	{
		if (dup_stdout(fd, fd->fdout) == FAILURE)
			exit_func(fd, FAILURE);
	}
	else if (cmd->pipe)
		if (dup_stdout(fd, fd->pipefd[1]) == FAILURE)
			exit_func(fd, FAILURE);
}
