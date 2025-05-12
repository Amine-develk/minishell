/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:34:25 by ael-krai          #+#    #+#             */
/*   Updated: 2025/05/12 13:55:46 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
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

// parsing
void	handle_signal(void);
void	signal_handler(int signal, siginfo_t *info, void *context);
int		check_parsing(char *str);
void	free_cmd(t_cmd **cmd);
int		is_operator(char c);
char	*ft_trim(char *str);
t_cmd	*create_cmd(char *str);
void	push_cmd(t_cmd **lst, t_cmd *cmd);

// execution
int	execute_cmd(t_cmd *cmd);

#endif