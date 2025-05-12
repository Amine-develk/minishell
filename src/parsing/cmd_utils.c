/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:15:43 by ael-krai          #+#    #+#             */
/*   Updated: 2025/05/12 13:30:49 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	if (!cmd)
		return ;
	while (*cmd)
	{
		tmp = *cmd;
		(*cmd) = (*cmd)->next;
		free(tmp);
	}
}

t_cmd	*create_cmd(char *str)
{
	t_cmd	*cmd;

	if (!(cmd = malloc(sizeof(t_cmd))))
		return (NULL);
	cmd->value = str;
	cmd->next = NULL;
	return (cmd);
}

void	push_cmd(t_cmd **lst, t_cmd *cmd)
{
	t_cmd	*tmp;

	if (!cmd || !lst)
		return ;
	if (!*lst)
	{
		*lst = cmd;
		return ;
	}
	tmp = (*lst);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = cmd;
}
