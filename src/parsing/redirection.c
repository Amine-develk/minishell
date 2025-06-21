/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:26:44 by ael-krai          #+#    #+#             */
/*   Updated: 2025/06/15 12:17:44 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*handle_pipe(t_cmd *cmd, t_cmd **cmds)
{
	t_cmd	*command;

	cmd->pipe = 1;
	push_cmd(cmds, cmd);
	command = init_cmd();
	if (!command)
		return (NULL);
	return (command);
}

void	update_redirection(char ***list, t_token *current)
{
	char	**new;
	int		i;

	if (!*list)
	{
		*list = ft_calloc(2, sizeof(char *));
		if (!*list)
			return ;
		(*list)[0] = ft_strdup(current->next->value);
		return ;
	}
	i = 0;
	while ((*list)[i])
		i++;
	new = ft_calloc(i + 2, sizeof(char *));
	if (!new)
		return ;
	i = -1;
	while ((*list)[++i])
		new[i] = (*list)[i];
	new[i] = ft_strdup(current->next->value);
	new[i + 1] = NULL;
	free(*list);
	*list = new;
}

void	process_redirection(t_cmd *cmd, t_token *current)
{
	if (current->next)
	{
		if (current->type == IN)
		{
			if (current->next)
				cmd->infile = ft_strdup(current->next->value);
		}
		else if (current->type == OUT || current->type == APPEND)
		{
			update_redirection(&cmd->outfile, current);
			if (current->type == APPEND)
				cmd->append = 1;
			if (current->type == OUT)
				cmd->append = 0;
		}
		else if (current->type == HEREDOC)
			update_redirection(&cmd->heredoc, current);
	}
}

void	parse_tokens(t_token *tokens, t_cmd **cmds)
{
	t_token	*token;
	t_cmd	*cmd;

	cmd = init_cmd();
	token = tokens;
	if (!cmd)
		return ;
	while (token)
	{
		if (token->type == WORD)
			cmd->args = ft_addstr(cmd->args, token->value);
		else if (token->type == PIPE)
			cmd = handle_pipe(cmd, cmds);
		else
		{
			process_redirection(cmd, token);
			if (token->next)
				token = token->next;
			else
				break ;
		}
		token = token->next;
	}
	push_cmd(cmds, cmd);
}
