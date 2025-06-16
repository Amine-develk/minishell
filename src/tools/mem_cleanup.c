/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnahli <mnahli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:39:46 by mnahli            #+#    #+#             */
/*   Updated: 2025/06/16 10:42:18 by mnahli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env(t_env **env)
{
	t_env	*tmp;

	if (!env || !*env)
		return ;
	while (*env)
	{
		tmp = *env;
		*env = (*env)->next;
		free(tmp->value);
		free(tmp);
	}
	*env = NULL;
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	free_command_fields(t_cmd *cmd)
{
	int	i;

	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
	}
	if (cmd->infile)
		free(cmd->infile);
	free_array(cmd->outfile);
	if (cmd->outfile)
		free(*cmd->outfile);
	free_array(cmd->heredoc);
	if (cmd->heredoc)
		free(*cmd->heredoc);
	if (cmd->cmd_path)
		free(cmd->cmd_path);
}

void	free_command_list(t_cmd **cmd_list)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!cmd_list || !*cmd_list)
		return ;
	current = *cmd_list;
	while (current)
	{
		next = current->next;
		free_command_fields(current);
		free(current);
		current = next;
	}
	*cmd_list = NULL;
}
