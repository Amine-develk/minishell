/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:34:20 by ael-krai          #+#    #+#             */
/*   Updated: 2025/05/11 11:30:17 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokanize(t_cmd **cmd_list, int t, char *line, int i, int len)
{
	t_cmd *cmd;

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
				ft_tokanize(cmd, 0, line, j, i - j);
			if (is_operator(line[i + 1]))
			{
				ft_tokanize(cmd, 2, line, i, 2);
				i += 2;
			}
			else
			{
				ft_tokanize(cmd, 1, line, i, 1);
				i++;
			}
			j = i;
		}
		else
			i++;
	}
	if (i > j)
		ft_tokanize(cmd, 0, line, j, i - j);
}

void	print_cmd(t_cmd *cmd)
{
	while (cmd != NULL)
	{
		if (cmd->type == 0)
		{
			int	i = 0;
			printf("%u:\t", cmd->type);
			while (cmd->args[i])
			{
				printf("%s\t", cmd->args[i]);
				i++;
			}
			printf("\n");
		}
		else
			printf("%u:\t%s\n", cmd->type, cmd->value);
		cmd = cmd->next;
	}

}

int	main()
{
	struct sigaction	action;
	t_cmd				*cmd;
	char				*line;

	action.sa_sigaction = signal_handler;
	sigaction(SIGINT, &action, NULL);
	sigaction(EOF, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
	cmd = NULL;
	while (1)
	{
		line = ft_trim(readline("minishell> "));
		if (line == NULL)
			break ;
		add_history(line);
		if (line == NULL)
			continue ;
		if (check_parsing(line))
			printf("Syntax Error\n");
		create_cmd_list(&cmd, line);
		print_cmd(cmd);
	}
	return (clear_history(), free_cmd(&cmd), free(line), 0);
}
  