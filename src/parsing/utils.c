/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 10:03:05 by ael-krai          #+#    #+#             */
/*   Updated: 2025/05/15 11:24:16 by ael-krai         ###   ########.fr       */
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
		rl_replace_line("", 0);
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

char	*ft_trim(char *s)
{
	char	*str;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = ft_strlen(s) - 1;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\"' || s[i] == '\'')
		i++;
	while (s[j] == ' ' || s[j] == '\t' || s[j] == '\"' || s[j] == '\'')
		j--;
	if (!(str = malloc(j - i + 1)))
		return (NULL);
	free(s);
	k = 0;
	while (i <= j)
		str[k++] = s[i++];
	return (str[k] = '\0', str);
}
