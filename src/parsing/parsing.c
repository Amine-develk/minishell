/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 09:20:43 by ael-krai          #+#    #+#             */
/*   Updated: 2025/06/21 11:53:12 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_increment(int *open, int *i, int n)
{
	(*i)++;
	(*open) = n;
}

int	open_quotes(char *line)
{
	int	open;
	int	i;

	open = 0;
	i = 0;
	while (line[i])
	{
		if (i > 0 && line[i - 1] == '\\')
			i++;
		else if (open == 0 && line[i] == '\"')
			ft_increment(&open, &i, 1);
		else if (open == 0 && line[i] == '\'')
			ft_increment(&open, &i, 2);
		else if ((open == 1 && line[i] == '\"')
			|| (open == 2 && line[i] == '\''))
			ft_increment(&open, &i, 0);
		else
			i++;
	}
	return (open);
}

t_type	get_type(char *line, int *i)
{
	if (line[*i] == '>' && line[*i + 1] == '>')
		return ((*i) += 2, APPEND);
	else if (line[*i] == '<' && line[*i + 1] == '<')
		return ((*i) += 2, HEREDOC);
	else if (line[*i] == '&' && line[*i + 1] == '&')
		return ((*i) += 2, AND);
	else if (line[*i] == '|' && line[*i + 1] == '|')
		return ((*i) += 2, OR);
	else if (line[*i] == '<')
		return ((*i)++, IN);
	else if (line[*i] == '>')
		return ((*i)++, OUT);
	else if (line[*i] == '|')
		return ((*i)++, PIPE);
	else
		return (WORD);
}

t_cmd	*ft_parse(char *line, t_env **env)
{
	t_cmd	*cmd;

	cmd = NULL;
	if (!line || !*line)
		return (NULL);
	if (open_quotes(line))
		return ((*env)->exit_code = 258,
			ft_putendl_fd(UNEXPECTED, 2), NULL);
	if (ambiguous_redirect(line, *env))
		return ((*env)->exit_code = 258,
			ft_putendl_fd("ambiguous redirect", 2), NULL);
	if (redirect_errors(line, 0, NULL) || pipe_errors(line))
		return ((*env)->exit_code = 258,
			ft_putendl_fd(UNEXPECTED, 2), NULL);
	cmd = tokenize_line(line, env);
	return (cmd);
}
