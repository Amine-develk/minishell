/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:15:43 by ael-krai          #+#    #+#             */
/*   Updated: 2025/05/15 10:01:36 by ael-krai         ###   ########.fr       */
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

void	free_env(t_env **env)
{
	t_env	*tmp;

	if (!env)
		return ;
	while (*env)
	{
		tmp = *env;
		(*env) = (*env)->next;
		free(tmp);
	}
}

t_env	*create_env(char *str)
{
	t_env	*env;

	if (!(env = malloc(sizeof(t_env))))
		return (NULL);
	env->value = str;
	env->next = NULL;
	return (env);
}

void	push_env(t_env **lst, t_env *env)
{
	t_env	*tmp;

	if (!env || !lst)
		return ;
	if (!*lst)
	{
		*lst = env;
		return ;
	}
	tmp = (*lst);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = env;
}