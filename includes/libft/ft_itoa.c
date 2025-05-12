/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 20:48:08 by ael-krai          #+#    #+#             */
/*   Updated: 2024/11/11 13:28:18 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	int_len(int n)
{
	int	c;

	c = 0;
	if (n == 0)
		c++;
	if (n < 0)
	{
		n *= -1;
		c++;
	}
	while (n > 0)
	{
		n = n / 10;
		c++;
	}
	return (c);
}

char	*ft_itoa(int c)
{
	char	*str;
	int		len;

	if (c == -2147483648)
		return (ft_strdup("-2147483648"));
	len = int_len(c);
	str = malloc(len + 1 * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	len--;
	if (c == 0)
		str[0] = '0';
	if (c < 0)
	{
		str[0] = '-';
		c *= -1;
	}
	while (c > 0)
	{
		str[len] = c % 10 + '0';
		c = c / 10;
		len--;
	}
	return (str);
}
