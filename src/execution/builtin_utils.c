/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnahli <mnahli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:42:55 by mnahli            #+#    #+#             */
/*   Updated: 2025/06/16 09:19:13 by mnahli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_var_value(char *var)
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

char	*get_var_name(char *var)
{
	int		i;
	char	*var_name;

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

int	is_valid_env_var_name(char *var)
{
	int		i;
	char	*var_name;

	if (!var || var[0] == '\0')
		return (0);
	var_name = get_var_name(var);
	if (!var_name || var_name[0] == '\0')
		return (free(var_name), 0);
	if (var_name[0] == '-' && var_name[1] == '-')
		return (free(var_name), 0);
	if (!isalpha(var_name[0]) && var_name[0] != '_')
		return (free(var_name), 0);
	i = 1;
	while (var_name[i])
	{
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_')
			return (free(var_name), 0);
		i++;
	}
	return (free(var_name), 1);
}
