/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 10:03:05 by ael-krai          #+#    #+#             */
/*   Updated: 2025/05/12 13:30:59 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_signal(void)
{
	struct sigaction	action;

	action.sa_sigaction = signal_handler;
	sigaction(SIGINT, &action, NULL);
	sigaction(EOF, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}

void	signal_handler(int signal, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signal == SIGINT)
	{
		printf("\n");
		// rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signal == EOF)
		exit(0);
}

int	is_operator(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
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
	if (str[i - j - 1] == '|' || str[i - j - 1] == '>' || str[i - j - 1] == '<'
		|| str[j] == '|' || d % 2 != 0 || s % 2 != 0)
		return (1);
	return (0);
}
