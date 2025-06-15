/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnahli <mnahli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:35:40 by mnahli            #+#    #+#             */
/*   Updated: 2025/06/14 13:26:41 by mnahli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	var_in_line(char *delimiter, char *line)
{
	int i;
	int dlm_len;

	if (!delimiter || !line)
		return (0);
	dlm_len = ft_strlen(delimiter);
	if (dlm_len == 0 || dlm_len == 1)
		return (0);
	if ((delimiter[0] == '\'' && delimiter[dlm_len - 1] == '\'')
		|| (delimiter[0] == '\"' && delimiter[dlm_len - 1] == '\"'))
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] && line[i + 1] != ' ' && line[i
			+ 1] != '\n')
			return (1);
		i++;
	}
	return (0);
}
