/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:00:39 by ael-krai          #+#    #+#             */
/*   Updated: 2025/05/31 12:27:26 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_var_name(char *var)
{
	char	*var_name;
	int		i;

	if (!var)
		return (NULL);
	i = 0;
	while (var[i] && !(var[i] == '+' && var[i + 1] == '=') && var[i] != '=')
		i++;
	var_name = (char *)malloc(sizeof(char) * (i + 1));
	if (!var_name)
		return (NULL);
	i = 0;
	while (var[i] && !(var[i] == '+' && var[i + 1] == '=') && var[i] != '=')
	{
		var_name[i] = var[i];
		i++;
	}
	var_name[i] = '\0';
	return (var_name);
}

char	*var_value(char *var)
{
	int	start;
	int	i;

	if (!var)
		return (NULL);
	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (!var[i] || !var[++i])
		return (NULL);
	start = i;
	while (var[i])
		i++;
	return (ft_substr(var, start, i - start));
}
