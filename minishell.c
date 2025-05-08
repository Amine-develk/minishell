/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:34:20 by ael-krai          #+#    #+#             */
/*   Updated: 2025/05/08 18:12:51 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_node(t_cmd **cmd_list, int t, char *line, int i, int len)
{
	t_cmd *cmd;

	if (!(cmd = create_cmd(ft_substr(line, i, len))))
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


void	create_cmd_list(t_cmd **cmd, char *line)
{
	int		i;
	int		j;
	int		quote;
	
	i = 0;
	j = 0;
	quote = 0;
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
			quote = !quote;
		if (is_operator(line[i]) && !quote)
		{
			if (i > j)
				handle_node(cmd, 0, line, j, i - j);
			if (is_operator(line[i + 1]))
			{
				handle_node(cmd, 2, line, i, 2);
				i += 2;
			}
			else
			{
				handle_node(cmd, 1, line, i, 1);
				i++;
			}
			j = i;
		}
		else
			i++;
	}
	if (i > j)
		handle_node(cmd, 0, line, j, i - j);
}

int	main()
{
	t_cmd	*cmd;
	char	*line;
	
	cmd = NULL;
	while (1)
	{
		line = readline("minishell> ");
		add_history(line);
		if (line == NULL)
			continue ;
		if (check_parsing(line))
			printf("ERROR\n");
		create_cmd_list(&cmd, line);
		while (cmd != NULL)
		{
			if (cmd->type == 0)
			{
				int	i = 0;
				while (cmd->args[i])
				{
					printf("%s\n", cmd->args[i]);
					i++;
				}
			}
			else
				printf("%s\n", cmd->value);
			printf("%u\n\n", cmd->type);
			cmd = cmd->next;
		}
		free_cmd(&cmd);
	}
	return (clear_history(), free(line), 0);
}
