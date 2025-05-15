/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:13:58 by ael-krai          #+#    #+#             */
/*   Updated: 2025/05/15 11:18:20 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_tokanize(t_cmd **cmd_list, t_cmd *cmd, int t, char *line, int i, int len)
{
	if (!(cmd = create_cmd(ft_trim(ft_substr(line, i, len)))))
		return ;
	if (t == 0)
	{
		cmd->args = ft_split(cmd->value, ' ');
		cmd->type = CMD;
	}
	else if (t == 1)
	{
		if (cmd->value[0] == '|')
			cmd->type = PIPE;
		else if (cmd->value[0] == '<')
			cmd->type = INPUT;
		else
			cmd->type = OUTPUT;
	}
	else
	{
		if (cmd->value[0] == '<')
			cmd->type = HEREDOC;
		else
			cmd->type = APPEND;
	}
	push_cmd(cmd_list, cmd);
}

void	create_cmd_list(t_cmd **cmd, t_cmd	*command, char *line, int quote, int i, int j)
{
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
			quote = !quote;
		if (is_operator(line[i]) && !quote)
		{
			if (i > j)
				ft_tokanize(cmd, command, 0, line, j, i - j);
			if (is_operator(line[i + 1]))
			{
				ft_tokanize(cmd, command, 2, line, i, 2);
				i += 2;
			}
			else
			{
				ft_tokanize(cmd, command, 1, line, i, 1);
				i++;
			}
			j = i;
		}
		else
			i++;
	}
	if (i > j)
		ft_tokanize(cmd, command, 0, line, j, i - j);
}