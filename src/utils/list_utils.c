/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:37:57 by ael-krai          #+#    #+#             */
/*   Updated: 2025/06/14 20:00:00 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_node(t_type type, char *value)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->value = value;
	node->type = type;
	node->next = NULL;
	return (node);
}

void	push_cmd(t_cmd **head, t_cmd *node)
{
	t_cmd	**last;

	last = head;
	if (!node || !head)
		return ;
	while (*last)
		last = &(*last)->next;
	*last = node;
}

void	push_back(t_token **head, t_type type, char *value)
{
	t_token	*new;
	t_token	*tmp;

	if (!value)
		return ;
	new = create_node(type, value);
	if (!new || !head)
		return ;
	if (*head == NULL)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
