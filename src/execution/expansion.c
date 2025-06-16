/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnahli <mnahli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:36:13 by mnahli            #+#    #+#             */
/*   Updated: 2025/06/16 09:58:01 by mnahli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expand_variables(t_env *env, char *line, int fd)
{
	char	*var_value;
	char	*var_name;

	int i, (j);
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] && ft_isalpha(line[i + 1]))
		{
			i++;
			j = 0;
			var_name = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1));
			if (!var_name)
				return ;
			while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
				var_name[j++] = line[i++];
			var_name[j] = '\0';
			var_value = get_env_value(env, var_name);
			if (var_value)
				ft_putstr_fd(var_value, fd);
			free(var_name);
		}
		else
			ft_putchar_fd(line[i++], fd);
	}
}
