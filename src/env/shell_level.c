/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:00:15 by ael-krai          #+#    #+#             */
/*   Updated: 2025/06/17 10:40:02 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**env_to_str(t_env *env)
{
	char	**str;
	int		i;

	i = 0;
	str = (char **)malloc(sizeof(char *) * (env_size(env) + 1));
	if (!str)
		return (NULL);
	while (env)
	{
		str[i] = ft_strdup(env->value);
		if (!str[i])
		{
			while (i--)
				free(str[i]);
			free(str);
			return (NULL);
		}
		env = env->next;
		i++;
	}
	return (str[i] = NULL, str);
}

void	handle_empty_env(t_env **env)
{
	char	*pwd;
	char	cwd[PATH_MAX];

	if (!env)
		return ;
	if (getcwd(cwd, sizeof(cwd)))
	{
		pwd = ft_strjoin("PWD=", cwd);
		if (pwd)
		{
			push_env(env, pwd);
			free(pwd);
		}
	}
	push_env(env, "SHLVL=1");
	push_env(env, "_=/usr/bin/env");
}

void	increment_shell(t_env **env)
{
	t_env	*current;
	char	*str;
	char	*new;
	int		level;

	level = 0;
	if (!env || !*env)
		return (handle_empty_env(env));
	current = *env;
	while (current && ft_strncmp(current->value, "SHLVL=", 6) != 0)
		current = current->next;
	if (!current)
		return (handle_empty_env(env));
	level = ft_atoi(current->value + 6) + 1;
	if (level > 1000)
		level = 1;
	if (level < 0)
		level = 0;
	str = ft_itoa(level);
	new = ft_strjoin("SHLVL=", str);
	free(str);
	if (!new)
		return ;
	free(current->value);
	current->value = new;
}
