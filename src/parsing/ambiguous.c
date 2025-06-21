/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:25:00 by ael-krai          #+#    #+#             */
/*   Updated: 2025/06/02 20:53:44 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_ambiguous(char *value)
{
	int	word_count;
	int	in_word;
	int	i;

	if (!value || !*value)
		return (1);
	word_count = 0;
	in_word = 0;
	i = 0;
	while (value[i])
	{
		if (value[i] != ' ' && !in_word)
		{
			in_word = 1;
			word_count++;
		}
		else if (value[i] == ' ')
			in_word = 0;
		i++;
	}
	return (word_count > 1);
}

static int	var_ambiguity(char *line, int *i, t_env *env)
{
	char	var_name[255];
	char	*value;
	int		j;

	j = 0;
	(*i)++;
	while ((ft_isalnum(line[*i]) || line[*i] == '_') && *i < 255)
		var_name[j++] = line[(*i)++];
	var_name[j] = '\0';
	value = get_env_value(env, var_name);
	return (is_ambiguous(value));
}

int	ambiguous_redirect(char *line, t_env *env)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<')
		{
			if (line[i] == '>' && line[i] == '>')
				i++;
			i++;
			while (line[i] == ' ')
				i++;
			if (line[i] == '$' && var_ambiguity(line, &i, env))
				return (1);
		}
		else
			i++;
	}
	return (0);
}
