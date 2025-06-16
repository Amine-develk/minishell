/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnahli <mnahli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:04:28 by mnahli            #+#    #+#             */
/*   Updated: 2025/06/16 09:18:33 by mnahli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	append_env_value(t_env *env, char *var)
{
	char	*new_var;
	char	*var_value;

	var_value = get_var_value(var);
	if (!var_value)
		return ;
	new_var = ft_strjoin(env->value, var_value);
	if (!new_var)
		return (free(var_value));
	free(env->value);
	free(var_value);
	env->value = new_var;
}

int	ft_env(t_env *env)
{
	if (!env)
		return (FAILURE);
	while (env)
	{
		if (ft_strchr(env->value, '='))
			ft_putendl_fd(env->value, 1);
		env = env->next;
	}
	return (SUCCESS);
}
