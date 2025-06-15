/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnahli <mnahli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:11:47 by mnahli            #+#    #+#             */
/*   Updated: 2025/06/14 11:12:09 by mnahli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	push_env_back(t_env **head, char *value)
{
	t_env	*tmp;
	t_env	*node;

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
