/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:45:39 by ael-krai          #+#    #+#             */
/*   Updated: 2024/11/11 10:27:03 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	s;
	int		i;

	s = (char) c;
	i = 0;
	while (str[i])
	{
		if (str[i] == s)
			return ((char *) &str[i]);
		i++;
	}
	if (str[i] == s)
		return ((char *) &str[i]);
	return (NULL);
}
