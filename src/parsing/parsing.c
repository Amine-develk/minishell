/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 08:30:00 by ael-krai          #+#    #+#             */
/*   Updated: 2025/05/15 11:05:59 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remove_quotes(char *str)
{
	char	*s;
	int		i;
	int		j;
	int		k;

	i = 1;
	j = ft_strlen(str) - 2;
	if (!(s = malloc(j - i + 1)))
		return (NULL);
	k = 0;
	while (i <= j)
	{
		s[k] = str[i];
		k++;
		i++;
	}
	return (s[k] = '\0', s);
}

int	check_quotes(char *str)
{
	int	i;
	int	d;
	int	s;

	i = 0;
	d = 0;
	s = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			d++;
		else if (str[i] == '\'')
			s++;
		i++;
	}
	if (d % 2 != 0 || s % 2 != 0)
		return (1);
	return (0);
}

int	check_operator(char *s)
{
	int	i;

	i = ft_strlen(s) - 1;
	if (s[0] == '|' || is_operator(s[i]))
		return (1);
	return (0);
}

int	check_parsing(char *str)
{
	if (check_quotes(str) || check_operator(str))
		return (1);
	return (0);
}