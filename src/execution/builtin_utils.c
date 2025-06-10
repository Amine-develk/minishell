/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnahli <mnahli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:42:55 by mnahli            #+#    #+#             */
/*   Updated: 2025/06/10 11:09:41 by mnahli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_var_name(char *var)
{
	int	i;
	char	*var_name;

	if (!var)
		return (NULL);
	i = 0;
	while (var[i] && !(var[i] == '+' && var[i + 1] == '=') && var[i] != '=')
		i++;
	var_name = malloc(sizeof(char) * (i + 1));
	if (!var_name)
		return (NULL);
	i = 0;
	while (var[i] && !(var[i] == '+' && var[i + 1] == '=') && var[i] != '=')
	{
		var_name[i] = var[i];
		i++;
	}
	return (var_name[i] = '\0', var_name);
}

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

// int	ft_env(t_env *env)
// {
// 	if (!env)
// 		return (FAILURE);
// 	while (env)
// 	{
// 		if (ft_strchr(env->value, '='))
// 			ft_putendl_fd(env->value, 1);
// 		env = env->next;
// 	}
// 	return (SUCCESS);
// }
