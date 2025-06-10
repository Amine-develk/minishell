/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnahli <mnahli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:19:45 by mnahli            #+#    #+#             */
/*   Updated: 2025/06/10 11:46:47 by mnahli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	heredoc_handeler(char *delimiter, t_env *env, int fd)
{
	char	*line;
	char	*line_delimiter;

	signal(SIGINT, signal_heredoc);
	line_delimiter = ft_strjoin(delimiter, "\n");
	if (!line_delimiter)
		return ;
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (!line || !ft_strcmp(line, line_delimiter))
			break ;
		if (var_in_line(line_delimiter, line))
			expand_variables(env, line, fd);
		else
			ft_putstr_fd(line, fd);
		free(line);
	}
	if (line)
		free(line);
	get_next_line(-1);
	free(line_delimiter);
	close(fd);
	exit(0);
}

int	ft_heredoc(char *delimiter, t_env *env)
{
	int	pid;
	int	status;
	int	fd;

	status = 0;
	signal(SIGINT, SIG_IGN);
	if (access("/tmp/here_doc", F_OK) == 0)
		unlink("/tmp/here_doc");
	fd = open("/tmp/here_doc", O_CREAT | O_TRUNC | O_WRONLY | 0644);
	if (fd == -1)
		return (perror("open"), exit(EXIT_FAILURE), FAILURE);
	pid = fork();
	if (pid == -1)
		return (close(fd), perror("fork"), exit(EXIT_FAILURE), FAILURE);
	if (pid == 0)
		heredoc_handeler(delimiter, env, fd);
	else
	{
		waitpid(pid, &status, 0);
		status = WEXITSTATUS(status);
	}
	if (status == 1)
		return (close(fd), g_exit_code = 1, FAILURE);
	return (close(fd), SUCCESS);
}
