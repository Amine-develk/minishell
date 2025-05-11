/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:34:25 by ael-krai          #+#    #+#             */
/*   Updated: 2025/05/11 11:27:21 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum    s_type
{
    CMD,
    PIPE,
    INPUT,
    OUTPUT,
    HEREDOC,
    APPEND
}   t_type;

typedef struct s_env
{
    char    		*value;
    struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
    char    		*value;
    char            **args;
	t_type          type;
    struct s_cmd	*next;
}	t_cmd;

// libft
void	*ft_free(char **str, int l);
size_t	ft_strlen(const char *str);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strdup(const char *str);
void	*ft_memset(void *str, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int     is_delim(char c, char delim, int in_squote, int in_dquote);
int     count_word(char const *s, char c);
char    *ft_subword(const char *s, int start, int end);
char	**ft_fill(char **split, const char *s, char c, int n);
char	**ft_split(char const *s, char c);

// utils
void	signal_handler(int signal, siginfo_t *d, void *context);
int		check_parsing(char *str);
void	free_cmd(t_cmd **cmd);
int		is_operator(char c);
char	*ft_trim(char *str);
t_cmd	*create_cmd(char *str);
void	push_cmd(t_cmd **lst, t_cmd *cmd);

#endif