/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:55:25 by ael-krai          #+#    #+#             */
/*   Updated: 2024/11/17 15:31:40 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen(src);
	i = 0;
	if (destsize == 0)
		return (src_len);
	while (src[i] && i < destsize - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (destsize != 0)
		dest[i] = '\0';
	return (src_len);
}
