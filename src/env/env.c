/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:33:40 by ael-krai          #+#    #+#             */
/*   Updated: 2025/06/15 13:45:05 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	push_env(t_env **head, char *value)
{
	t_env	*node;
	t_env	*tmp;

	if (!head || !value)
		return ;
	node = malloc(sizeof(t_env));
	if (!node)
		return ;
	node->value = ft_strdup(value);
	if (!node->value)
	{
		free(node);
		return ;
	}
	node->next = NULL;
	if (!*head)
		*head = node;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

int	init_env(t_env **env, char **envp)
{
	int	i;

	i = 0;
	if (!env || !envp)
		return (0);
	*env = NULL;
	while (envp[i])
		push_env(env, envp[i++]);
	return (1);
}
