/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnahli <mnahli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:24:26 by mnahli            #+#    #+#             */
/*   Updated: 2025/06/10 11:24:27 by mnahli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*ft_readline(int fd, char *rest);
void	free_str(char **str);
char	*extract_line(char *rest);
char	*up_rest(char **rest);
int		gnl_strchr(const char *s, int c);
size_t	gnl_strlen(const char *s);
size_t	gnl_strlcpy(char *dst, const char *src, size_t dstsize);
char	*gnl_strjoin(char *s1, char *s2);
char	*gnl_strdup(const char *s);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

#endif