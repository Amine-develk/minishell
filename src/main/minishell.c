/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnahli <mnahli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:34:20 by ael-krai          #+#    #+#             */
/*   Updated: 2025/05/27 13:07:31 by mnahli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		g_exit_code;

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

void	create_env_list(t_env **env, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		push_env(env, create_env(envp[i]));
		i++;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	t_cmd	*cmd;
	t_cmd	*command;
	char	**path;
	char	*line;
	int fd;

	(void)ac;
	(void)av;
	env = NULL;
	cmd = NULL;
	command = NULL;
	path = ft_split(envp[4] + 5, ':');
	create_env_list(&env, envp);
	handle_signal();
	while (1)
	{
		if (!(line = ft_trim(readline("minishell> "))))
			break ;
		add_history(line);
		if (line == NULL)
			continue ;
		if (check_parsing(line))
			printf("Syntax Error\n");
		create_cmd_list(&cmd, command, line, 0, 0, 0);
		print_cmd(cmd);
		free(line);
		free_cmd(&cmd);
	}
	return (clear_history(), free_env(&env), 0);
}

// hayd single and double quotes
// trim tabs
// syntax error cases bash
// check successive operators
// environment \/