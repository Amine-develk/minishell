/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnahli <mnahli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:04:28 by mnahli            #+#    #+#             */
/*   Updated: 2025/06/14 11:01:28 by mnahli           ###   ########.fr       */
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

void	print_value(char *var_name, char *var_value)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(var_name, STDOUT_FILENO);
	if (var_value && ft_strcmp(var_name, "OLDPWD") != 0)
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(var_value, STDOUT_FILENO);
		ft_putchar_fd('\"', STDOUT_FILENO);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	sort_env(char **env_arr)
{
	int		i;
	int		j;
	char	*tmp;

	if (!env_arr)
		return ;
	i = 0;
	while (env_arr[i])
	{
		j = 0;
		while (env_arr[j + 1])
		{
			if (ft_strcmp(env_arr[j], env_arr[j + 1] > 0))
			{
				tmp = env_arr[j];
				env_arr[j] = env_arr[j + 1];
				env_arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	print_sorted_env(t_env *env)
{
	char	**env_arr;
	int		i;
	char	*var_name;
	char	*var_value;

	env_arr = env_to_str(env);
	i = 0;
	if (!env_arr)
		return (FAILURE);
	sort_env(env_arr);
	while (env_arr[i])
	{
		var_name = get_var_name(env_arr[i]);
		var_value = get_var_value(env_arr[i]);
		if (var_name)
		{
			print_value(var_name, var_value);
			free(var_name);
			free(var_value);
		}
		i++;
	}
	free_array(env_arr);
	return (SUCCESS);
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
