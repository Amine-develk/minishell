/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 10:29:54 by ael-krai          #+#    #+#             */
/*   Updated: 2025/05/31 10:04:39 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_token(t_token **token)
{
	t_token	*current;
	t_token	*next;

	if (!token || !(*token))
		return ;
	current = *token;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	*token = NULL;
}

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

void	free_cmd_fields(t_cmd *cmd)
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

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!cmd || !*cmd)
		return ;
	current = *cmd;
	while (current)
	{
		next = current->next;
		free_cmd_fields(current);
		free(current);
		current = next;
	}
	*cmd = NULL;
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
