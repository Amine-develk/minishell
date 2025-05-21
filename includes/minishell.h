/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnahli <mnahli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:34:25 by ael-krai          #+#    #+#             */
/*   Updated: 2025/05/21 11:29:59 by mnahli           ###   ########.fr       */
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

// define APPEND_ERROR "minishell: syntax error near unexpected token `>>'"
// #define APPEND_ERROR "minishell: syntax error near unexpected token `<<'"
// #define APPEND_ERROR "minishell: syntax error near unexpected token `>>'"
// #define APPEND_ERROR "minishell: syntax error near unexpected token `>>'"
// #define APPEND_ERROR "minishell: syntax error near unexpected token `>>'"#

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
    char            **cmd_path;
	t_type          type;
    struct s_cmd	*next;
}	t_cmd;

typedef struct s_fd
{
	int					pipefd[2];
	int					fdin;
	int					fdout;
}						t_fd;

// parsing
char	*remove_quotes(char *str);
int	    check_quotes(char *str);
int	    check_operator(char *s);
int		check_parsing(char *str);

// utils
int		is_operator(char c);
char	*ft_trim(char *str);
void	handle_signal(void);
void	signal_handler(int signal, siginfo_t *info, void *context);

// cmd utils
void	free_cmd(t_cmd **cmd);
t_cmd	*create_cmd(char *str);
void	push_cmd(t_cmd **lst, t_cmd *cmd);
void	free_env(t_env **env);
t_env	*create_env(char *str);
void	push_env(t_env **lst, t_env *env);

// init cmd
void	ft_tokanize(t_cmd **cmd_list, t_cmd *cmd, int t, char *line, int i, int len);
void	create_cmd_list(t_cmd **cmd, t_cmd	*command, char *line, int quote, int i, int j);

// execution
void	exec(t_cmd **cmd, t_env **env, char **envp, t_fd *fd);
int	resolve_cmd_path(char **envp, t_cmd *cmd);

#endif