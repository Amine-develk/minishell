/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:51:01 by ael-krai          #+#    #+#             */
/*   Updated: 2024/11/21 13:14:16 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
