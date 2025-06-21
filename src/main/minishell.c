/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 09:25:45 by ael-krai          #+#    #+#             */
/*   Updated: 2025/06/21 11:51:20 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_exit_code;

void	process_line(t_cmd **cmd, t_env **env, char *line)
{
	char	**envp;
	t_fd	fd;

	init_fds(&fd);
	envp = env_to_str(*env);
	if (*line)
		add_history(line);
	*cmd = ft_parse(line, env);
	if (!*cmd)
	{
		free_cmd(cmd);
		free_array(envp);
		free(line);
		return ;
	}
	// ft_exec(cmd, env, envp, &fd);
	free(cmd);
	free(envp);
	free(line);
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	*cmd;
	t_env	*env;
	char	*line;

	(void)ac;
	(void)av;
	cmd = NULL;
	handle_signals();
	init_env(&env, envp);
	increment_shell(&env);
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		process_line(&cmd, &env, line);
	}
	free_env(&env);
	reset_terminal();
	return (env->exit_code);
}
