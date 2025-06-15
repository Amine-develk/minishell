/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_lvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnahli <mnahli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:51:31 by mnahli            #+#    #+#             */
/*   Updated: 2025/06/14 09:49:39 by mnahli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_size(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

char	**env_to_str(t_env *env)
{
	char	**str_env;
	int		i;

	i = 0;
	str_env = (char **)malloc(sizeof(char *) * (env_size(env) + 1));
	if (!str_env)
		return (NULL);
	while (env)
	{
		str_env[i] = ft_strdup(env->value);
		if (!str_env[i])
		{
			while (i--)
				free(str_env[i]);
			free(str_env);
			return (NULL);
		}
		env = env->next;
		i++;
	}
	str_env[i] = NULL;
	return (str_env);
}
