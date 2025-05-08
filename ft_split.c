/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:05:30 by ael-krai          #+#    #+#             */
/*   Updated: 2025/04/14 10:42:17 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	count_word(char const *s, char c)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			n++;
		i++;
	}
	return (n);
}

void	*ft_free(char **str, int l)
{
	while (l >= 0)
	{
		free(str[l]);
		l--;
	}
	free(str);
	return (NULL);
}

char	**ft_fill(char **str, char const *s, char c, int n)
{
	int	l;
	int	i;
	int	j;

	i = 0;
	j = 0;
	l = 0;
	while (l < n && s[i])
	{
		i = j;
		while (s[i] == c || (i != 0 && s[i - 1] != c))
			i++;
		j = i;
		while (s[j] != c && s[j] != '\0')
			j++;
		str[l] = ft_substr(s, i, j - i);
		if (!str[l])
			return (ft_free(str, l));
		l++;
	}
	str[l] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		n;

	str = NULL;
	if (!s)
		return (NULL);
	n = count_word(s, c);
	str = malloc((n + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	str = ft_fill(str, s, c, n);
	return (str);
}
