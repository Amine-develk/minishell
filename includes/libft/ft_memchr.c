/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:52:23 by ael-krai          #+#    #+#             */
/*   Updated: 2024/11/11 10:05:47 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	l;
	size_t			i;

	ptr = (unsigned char *) s;
	l = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == l)
			return ((void *) &ptr[i]);
		i++;
	}
	return (NULL);
}
