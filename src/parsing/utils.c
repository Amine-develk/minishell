/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:37:48 by ael-krai          #+#    #+#             */
/*   Updated: 2025/06/21 11:43:53 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->heredoc = NULL;
	cmd->pipe = 0;
	cmd->next = NULL;
	cmd->pid = -1;
	cmd->cmd_path = NULL;
	return (cmd);
}

char	*add_result(char *result, char *tmp)
{
	char	*new;

	if (!tmp)
		tmp = ft_strdup("");
	if (!result)
		return (tmp);
	new = ft_strjoin(result, tmp);
	free(result);
	free(tmp);
	return (new);
}

t_cmd	*tokenize_line(char *line, t_env **env)
{
	t_token	*token;
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = NULL;
	token = NULL;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t' || line[i] == '\r')
			i++;
		else
			process_and_add_token(&token, env, line, &i);
	}
	parse_tokens(token, &cmd);
	free_token(&token);
	return (cmd);
}
