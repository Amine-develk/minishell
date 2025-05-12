/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 20:25:51 by ael-krai          #+#    #+#             */
/*   Updated: 2024/11/09 18:59:04 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	j;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		if (ft_strchr(set, s1[i]) == NULL)
			break ;
		i++;
	}
	j = ft_strlen(s1);
	while (j > i)
	{
		if (ft_strchr(set, s1[j]) == NULL)
			break ;
		j--;
	}
	return (ft_substr(s1, i, j - i + 1));
}
