/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:13:28 by ael-krai          #+#    #+#             */
/*   Updated: 2025/06/21 11:54:34 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_operator(char *line, int i)
{
	return ((line[i] == '<' && line[i + 1] == '<')
		|| (line[i] == '>' && line[i + 1] == '>')
		|| (line[i] == '|' && line[i + 1] == '|')
		|| (line[i] == '&' && line[i + 1] == '&')
		|| line[i] == '|' || line[i] == '<' || line[i] == '>');
}

int	check_semicolon(char *line)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '|' && line[i + 1] == '|' && line[i + 2] == '|')
			return (1);
		if (line[i] == '"' || line[i] == '\'')
		{
			if (quote == 0)
				quote = line[i];
			else if (quote == line[i])
				quote = 0;
		}
		else if (line[i] == ';' && quote == 0)
			return (1);
		i++;
	}
	return (0);
}

char	*extract_filename(char *line)
{
	char	*file;
	char	*tmp;
	int		i;
	int		j;

	file = NULL;
	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\r')
		i++;
	if (line[i] == '"' || line[i] == '\'')
		i++;
	j = i;
	while (line[i] && line[i] != ' ' && line[i] != '"' && line[i] == '\''
		&& line[i] != '|' && line[i] != '<' && line[i] != '>')
		i++;
	tmp = ft_substr(line, j, i - j);
	if (tmp)
	{
		file = ft_strdup(tmp);
		free(tmp);
	}
	return (file);
}

int	pipe_errors(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\r')
		i++;
	if (line[i] == '|')
		return (g_exit_code = 258, ft_putendl_fd(UNEXPECTED_TOKEN, 2), 1);
	while (line[i])
	{
		if (line[i] == '|' && line[i + 1] != '|')
		{
			i++;
			while (line[i] == ' ' || line[i] == '\t' || line[i] == '\r')
				i++;
			if (line[i] == '|' || line == '\0')
				return (g_exit_code = 258,
					ft_putendl_fd(UNEXPECTED_TOKEN, 2), 1);
		}
		i++;
	}
	return (0);
}

int	redirect_errors(char *line, int i, char *file)
{
	while (line[i])
	{
		if (check_semicolon(line))
			return (g_exit_code = 2, ft_putendl_fd(UNEXPECTED, 2), 1);
		if ((line[i] == '<' && line[i + 1] != '<')
			|| (line[i] == '>' && line[i + 1] != '>'))
		{
			i++;
			while (line[i] == ' ' || line[i] == '\t' || line[i] == '\r')
				i++;
			if (!line[i] || line[i] == '~' || line[i] == '>'
				|| line[i] == '<' || line[i] == '|')
				return (g_exit_code = 2, ft_putendl_fd(UNEXPECTED_TOKEN, 2), 1);
			file = extract_filename(&line[i]);
			if (access(file, F_OK) == -1
				&& (line[i] == '>' && line[i - 1] != '>')
				&& (line[i] == '<' && line[i - 1] != '<'))
				return (g_exit_code = 2, perror(file), free(file), 1);
			free(file);
		}
		i++;
	}
	return (0);
}
