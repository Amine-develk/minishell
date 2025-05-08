/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:39:25 by ael-krai          #+#    #+#             */
/*   Updated: 2025/04/14 10:39:40 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	i = 0;
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	return (str);
}

char	*ft_strdup(const char *str)
{
	char		*s;
	size_t		i;
	size_t		n;

	n = ft_strlen(str);
	i = 0;
	s = malloc(n + 1 * sizeof(char));
	if (!s)
		return (NULL);
	while (str[i])
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

void	*ft_memset(void *str, int c, size_t len)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	n;

	s = (unsigned char *) str;
	n = (unsigned char) c;
	i = 0;
	while (i < len)
	{
		s[i] = n;
		i++;
	}
	return (s);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	memsize;

	if (count != 0 && size > SIZE_MAX / count)
		return (NULL);
	memsize = count * size;
	ptr = malloc(memsize);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, memsize);
	return (ptr);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
