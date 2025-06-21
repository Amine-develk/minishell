/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:49:06 by ael-krai          #+#    #+#             */
/*   Updated: 2025/06/21 11:43:09 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_char(char c, char **value)
{
	char	str[2];
	char	*tmp;

	str[0] = c;
	str[1] = '\0';
	tmp = *value;
	*value = ft_strjoin(*value, str);
	free(tmp);
}

void	expand_env(char *line, int *i, t_env **env, char **result)
{
	(*i)++;
	if (line[*i] == '?')
	{
		*result = add_result(*result, ft_itoa((*env)->exit_code));
		if (line[*i + 1] == '|')
			(*env)->exit_code = 0;
		return ;
	}
	if (ft_isdigit(line[*i]))
	{
		(*i)++;
		return ;
	}
	process_env_var(line, i, env, result);
}

char	*handle_quotes(char *line, int *i, t_env **env, char quote)
{
	char	*result;
	int		start;

	result = ft_strdup("");
	start = ++(*i);
	while (line[*i] && line[*i] != quote)
	{
		if (quote == '"' && line[*i] == '$' && (ft_isalnum(line[*i + 1]) 
				|| line[*i + 1] == '_' || line[*i + 1] == '?'))
		{
			if (*i > start)
				result = add_result(result, ft_substr(line, start, *i - start));
			expand_env(line, i, env, &result);
			start = *i;
		}
		else
			(*i)++;
	}
	if (*i > start)
		result = add_result(result, ft_substr(line, start, *i - start));
	if (line[*i] == quote)
		(*i)++;
	return (result);
}

void	process_word(char *line, int *i, t_env **env, char **value)
{
	char	*quote;
	char	*home;
	char	*tmp;

	skip_dollar(line, i);
	if (line[*i] == '\'' || line[*i] == '"')
	{
		quote = &line[*i];
		tmp = handle_quotes(line, i, env, *quote);
		if (tmp)
			*value = add_result(*value, tmp);
	}
	else if (line[*i] == '$' && (ft_isalnum(line[*i + 1])
			|| line[*i + 1] == '_' || line[*i + 1] == '?'))
		expand_env(line, i, env, value);
	else if (line[*i] == '~' && (*i == 0 || line[*i - 1] == ' ')
		&& (!line[*i + 1] || line[*i + 1] == ' ' || line[*i + 1] == '/'))
	{
		(*i)++;
		home = get_env_value(*env, "HOME");
		if (home)
			*value = add_result(*value, ft_strdup(home));
	}
	else
		handle_char(line[(*i)++], value);
}

void	process_and_add_token(t_token **token, t_env **env, char *line, int *i)
{
	t_type	tmp;
	char	*value;
	int		quotes;

	quotes = 0;
	if (is_operator(line, *i))
	{
		tmp = get_type(line, i);
		push_back(token, tmp, ft_strdup(""));
	}
	else
	{
		tmp = WORD;
		value = ft_strdup("");
		while (line[*i] && line[*i] != ' ' && !is_operator(line, *i))
		{
			if (line[*i] == '\'' || line[*i] == '"')
				quotes = 1;
			process_word(line, i, env, &value);
		}
		if ((value && *value) || quotes)
			push_back(token, tmp, value);
		else
			free(value);
	}
}
