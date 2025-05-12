/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:31:13 by ael-krai          #+#    #+#             */
/*   Updated: 2024/11/17 15:38:41 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
