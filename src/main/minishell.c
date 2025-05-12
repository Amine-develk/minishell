/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:34:20 by ael-krai          #+#    #+#             */
/*   Updated: 2025/05/12 13:55:00 by ael-krai         ###   ########.fr       */
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

int	main(int ac, char **av, char **envp)
{
	t_cmd				*cmd;
	t_cmd				*command;
	char				**env;
	char				*line;

	(void)ac;
	(void)av;
	cmd = NULL;
	command = NULL;
	env = ft_split(envp[4] + 5, ':');
	handle_signal();
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
		create_cmd_list(&cmd, command, line, 0, 0, 0);
		execute_cmd(cmd);
		print_cmd(cmd);
		free(line);
		free_cmd(&cmd);
	}
	return (clear_history(), 0);
}
