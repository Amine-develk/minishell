/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnahli <mnahli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:13:06 by mnahli            #+#    #+#             */
/*   Updated: 2025/06/16 09:25:15 by mnahli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_var(char *var)
{
	char	*var_name;
	char	*var_value;
	char	*val;

	var_name = get_var_name(var);
	if (!var_name)
		return (NULL);
	var_value = get_var_value(var);
	if (!var_value)
	{
		var_value = ft_strdup("");
		if (!var_value)
			return (free(var_name), NULL);
	}
	val = var_name;
	var_name = ft_strjoin(val, "=");
	free(val);
	if (!var_name)
		return (free(var_value), NULL);
	val = ft_strjoin(var_name, var_value);
	if (!val)
		return (free(var_name), free(var_value), NULL);
	free(var_name);
	free(var_value);
	return (val);
}

int	is_var_in_env(char *var, t_env *env, char *var_name)
{
	char	*env_var_name;
	char	*new_var;

	if (!var_name)
		return (0);
	while (env)
	{
		env_var_name = get_var_name(env->value);
		if (env_var_name && !ft_strcmp(var_name, env_var_name))
		{
			if (ft_strchr(var, '+'))
				return (append_env_value(env, var), free(env_var_name), 1);
			free(env->value);
			new_var = get_var(var);
			if (new_var)
				env->value = new_var;
			return (free(env_var_name), 1);
		}
		if (env_var_name)
			free(env_var_name);
		env = env->next;
	}
	return (0);
}

int	print_env_error(char *var, int errn)
{
	if (errn == 1)
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(var, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("minishell: export: -", STDERR_FILENO);
		ft_putchar_fd(var[1], STDERR_FILENO);
		ft_putendl_fd(": invalid option", STDERR_FILENO);
		ft_putstr_fd("export: usage: export [-nf] [name[=value]] ", 2);
			// ?? value]] or value]
		ft_putendl_fd("or export -p", 2);
	}
	return (FAILURE);
}

void	var_handler(t_env **env, char *arg)
{
	char	*var;
	char	*var_name;

	var_name = get_var_name(arg);
	if (!is_var_in_env(arg, *env, var_name))
	{
		if (ft_strchr(arg, '='))
		{
			var = get_var(arg);
			if (var)
			{
				push_env_back(env, var);
				free(var);
			}
		}
		else
			push_env_back(env, arg);
	}
	if (var_name)
		free(var_name);
}

int	ft_export(char **args, t_env **env)
{
	int	i;
	int	had_error;

	had_error = 0;
	i = 1;
	if (!args[1])
		return (print_sorted_env(*env), 0);
	while (args[i])
	{
		if (args[i][0] == '-' && (args[i][1] == '-' || ft_isalpha(args[i][1])))
		{
			print_env_error(args[i], 2);
			had_error = 2;
			i++;
			continue ;
		}
		if (!is_valid_env_var_name(args[i]))
			had_error = print_env_error(args[i], 1);
		else
			var_handler(env, args[i]);
		i++;
	}
	return (had_error);
}
