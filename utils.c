/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 10:03:05 by ael-krai          #+#    #+#             */
/*   Updated: 2025/05/11 11:31:07 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signal, siginfo_t *d, void *context)
{
	(void)context;
	(void)d;

	if (signal == SIGINT)
	{
		printf("\n");
		// rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signal == EOF || signal == SIGQUIT)
		exit(0) ;
}

int	is_operator(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return(0);
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	if (!cmd)
		return ;
	while (*cmd)
	{
		tmp = *cmd;
		(*cmd) = (*cmd)->next;
		free(tmp);
	}
}

char	*ft_trim(char *str)
{
	char	*s;
	int		start;
	int		end;
	int		len;
	int		i;

	if (!str)
		return (NULL);
	start = 0;
	while (str[start] && str[start] == ' ')
		start++;
	end = ft_strlen(str);
	while (end > start && str[end - 1] == ' ')
		end--;
	len = end - start;
	if (!(s = malloc(len + 1)))
		return (free(str), NULL);
	i = 0;
	while (i < len)
	{
		s[i] = str[start + i];
		i++;
	}
	return (free(str), s[len] = '\0', s);
}


int	check_parsing(char *str)
{
	int	i;
	int	j;
	int	d;
	int	s;

	i = 0;
	d = 0;
	s = 0;
	if (str[0] == '\'' || str[0] == '\"')
		j = 1;
	else
		j = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			d++;
		else if (str[i] == '\'')
			s++;
		i++;
	}
	if (d % 2 != 0 || s % 2 != 0 || str[j] == '|' ||
		str[i - j - 1] == '|' || str[i - j - 1] == '>' || str[i - j - 1] == '<')
		return (1);
	return (0);
}

t_cmd	*create_cmd(char *str)
{
	t_cmd	*cmd;

	if (!(cmd = malloc(sizeof(t_cmd))))
		return (NULL);
	cmd->value = str;
	cmd->next = NULL;
	return (cmd);
}

void	push_cmd(t_cmd **lst, t_cmd *cmd)
{
	t_cmd	*tmp;

	if (!cmd || !lst)
		return ;
	if (!*lst)
	{
		*lst = cmd;
		return ;
	}
	tmp = (*lst);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = cmd;
}
