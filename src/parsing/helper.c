/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:35:04 by ael-krai          #+#    #+#             */
/*   Updated: 2025/06/21 11:40:52 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	skip_dollar(char *line, int *i)
{
	if ((line[*i] == '$' && line[*i + 1] == '"')
		|| (line[*i] == '$' && line[*i + 1] == '\''))
		(*i)++;
}

char	*trim_env(char *s)
{
	char	*value;
	int		start;
	int		i;

	if (ft_strlen(s) == 0)
		return (ft_strdup(""));
	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t' || s[i] == '\r'))
		i++;
	start = i;
	while (s[i] && !(s[i] == ' ' || s[i] == '\t' || s[i] == '\r'))
		i++;
	value = ft_substr(s, start, i - start);
	if (!value)
		return (ft_strdup(""));
	return (value);
}

void	process_env_var(char *line, int *i, t_env **env, char **result)
{
	char	*res;
	char	*t;
	char	*v;
	int		j;

	j = *i;
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		(*i)++;
	if (*i > j)
	{
		t = ft_substr(line, j, *i - j);
		if (t)
		{
			v = get_env_value(*env, t);
			if (v)
			{
				res = trim_env(v);
				if (res)
					*result = add_result(*result, res);
			}
			else
				*result = add_result(*result, ft_strdup(""));
			free(t);
		}
	}
}
