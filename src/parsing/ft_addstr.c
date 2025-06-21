/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 09:14:27 by ael-krai          #+#    #+#             */
/*   Updated: 2025/06/14 11:56:58 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_addstr(char **arr, char *str)
{
	char	**new;
	int		i;

	i = 0;
	if (!arr)
	{
		new = malloc(sizeof(char *) * 2);
		if (!new)
			return (NULL);
		new[0] = ft_strdup(str);
		new[1] = NULL;
		return (new);
	}
	while (arr[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (NULL);
	ft_memcpy(new, arr, i * sizeof(char *));
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
	free(arr);
	return (new);
}
