/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnahli <mnahli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:40:25 by mnahli            #+#    #+#             */
/*   Updated: 2025/05/12 12:05:32 by mnahli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
// input: t_fd *fd, t_command *cmds, t_env **env, char **envp
int	ft_exec_cmd()
{
	
}


void	exec()
{
	resolve_cmd_path();
	ft_exec_cmd();
}


// int	execute_cmd(t_cmd *cmd)
// {
// 	pid_t	pid;
// 	int		status;

// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		perror("fork");
// 		return (1);
// 	}
// 	if (pid == 0)
// 	{
// 		if (execve("/bin/ls", cmd->args, NULL) == -1)
// 		{
// 			perror("execve");
// 			exit(1);
// 		}
// 	}
// 	else
// 	{
// 		waitpid(pid, &status, 0);
// 	}
// 	return (0);
// }