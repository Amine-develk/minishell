/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:06:18 by ael-krai          #+#    #+#             */
/*   Updated: 2025/06/21 11:45:41 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(t_env *env, const char *key)
{
	char	*var_name;

	while (env)
	{
		var_name = get_var_name(env->value);
		if (ft_strcmp(var_name, key) == 0)
		{
			free(var_name);
			if (env->value)
				return (env->value + ft_strlen(key) + 1);
			else
				break ;
		}
		free(var_name);
		env = env->next;
	}
	return (NULL);
}
