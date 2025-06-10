/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnahli <mnahli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:44:03 by mnahli            #+#    #+#             */
/*   Updated: 2025/05/23 17:27:47 by mnahli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_path(char **envp)
{
	char	**path;
	int		i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			path = ft_split(envp[i] + 5, ':');
			if (!path)
				return (NULL);
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char **path, char *cmd)
{
	int		i;
	char	*full_path;
	char	*temp;

	i = 0;
	if (!path || !*path || !cmd || !*cmd)
		return (NULL);
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		if (!temp)
			return (NULL);
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

int	resolve_cmd_path(char **envp, t_cmd *cmd)
{
	char	**path;

	if (!envp || !*envp || !cmd)
		return (0);
	path = get_path(envp);
	while (cmd)
	{
		if (cmd->args && cmd->args[0])
		{
			if (ft_strchr(cmd->args[0], '/') || !(ft_strncmp(cmd->args[0], "./",
						2)))
				cmd->cmd_path = ft_strdup(cmd->args[0]);
			else if (path)
				cmd->cmd_path = get_cmd_path(path, cmd->args[0]);
		}
		cmd = cmd->next;
	}
	free_array(path);
	return (1);
}

/*
example iput: minishell$ ls -l

Input values:
cmd = ls -l | grep txt | wc -l
cmds:     [ls -l] → [grep txt] → [wc -l] → NULL


cmds->args = {"ls", "-l", NULL};     // From user input
cmds->args[0] = "ls";                // First argument: command name

cmds->args = {"/bin/echo", "hello", NULL};
cmds->args[0] = "/bin/echo";

cmds->args = {"./my_script.sh", NULL};
cmds->args[0] = "./my_script.sh";
------------------

envp = {
  "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin",
  ...
};

get_paths(envp)
Returns:
paths = {
  "/usr/local/bin",
  "/usr/bin",
  "/bin",
  "/usr/sbin",
  "/sbin",
  NULL
};

get_cmd_path(paths, "ls")
/usr/local/bin/ls    ✗
/usr/bin/ls          ✓ FOUND!
cmds->cmd_path = "/usr/bin/ls";


*/