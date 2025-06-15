/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnahli <mnahli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:34:25 by ael-krai          #+#    #+#             */
/*   Updated: 2025/06/14 13:17:01 by mnahli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>

# define FAILURE 1
# define SUCCESS 0
// #define APPEND_ERROR "minishell: syntax error near unexpected token `>>'"
// #define APPEND_ERROR "minishell: syntax error near unexpected token `<<'"
// #define APPEND_ERROR "minishell: syntax error near unexpected token `>>'"
// #define APPEND_ERROR "minishell: syntax error near unexpected token `>>'"
// #define APPEND_ERROR "minishell: syntax error near unexpected token `>>'"#

// just to silent the error
int					g_exit_code;
// end silenting the error
typedef enum s_type
{
	CMD,
	PIPE,
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND
}					t_type;

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_cmd
{
	char *value; // zayda
	char			**args;
	char			**heredoc;
	char *cmd_path; // 2 stars or one star
	pid_t			pid;
	char			*infile;
	char			**outfile;
	int				pipe;
	int				append;
	t_type			type;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_fd
{
	int				pipefd[2];
	int				fdin;
	int				fdout;
}					t_fd;

// parsing
char				*remove_quotes(char *str);
int					check_quotes(char *str);
int					check_operator(char *s);
int					check_parsing(char *str);

// utils
int					is_operator(char c);
char				*ft_trim(char *str);
void				handle_signal(void);
void				signal_handler(int signal, siginfo_t *info, void *context);

// cmd utils
void				free_cmd(t_cmd **cmd);
t_cmd				*create_cmd(char *str);
void				push_cmd(t_cmd **lst, t_cmd *cmd);
void				free_env(t_env **env);
t_env				*create_env(char *str);
void				push_env(t_env **lst, t_env *env);

// init cmd
void				ft_tokanize(t_cmd **cmd_list, t_cmd *cmd, int t, char *line,
						int i, int len);
void				create_cmd_list(t_cmd **cmd, t_cmd *command, char *line,
						int quote, int i, int j);

// execution
void				exec(t_cmd **cmd, t_env **env, char **envp, t_fd *fd);
int					resolve_cmd_path(char **envp, t_cmd *cmd);
int					ft_heredoc(char *delimiter, t_env *env);
void				signal_heredoc(int sig);
int					var_in_line(char *delimiter, char *line);
void				expand_variables(t_env *env, char *line, int fd);
char				*get_env_value(t_env *env, const char *key);
char				*get_var_name(char *var);
void				setup_signals(void);
char				*get_next_line(int fd);
int					open_redir(t_cmd *current, t_fd *fd);
char				**get_path(char **envp);
int					is_builtin(char *command);
void				close_fds(t_fd *fd);
int					dup_stdout(t_fd *fd, int newfd);
int					dup_stdin(t_fd *fd, int newfd);
void				exec_builtin(char **args, t_env **env);

// built_ins functions
int					exec_bltin(t_cmd *current, t_env **env, t_fd *fd);
int					ft_echo(char **args);
int					ft_cd(char **args, t_env **env);
int					ft_pwd(void);
int					print_sorted_env(t_env *env);

char				**env_to_str(t_env *env);
char				*get_var_value(char *var);
int					is_valid_env_var_name(char *var);
void				append_env_value(t_env *env, char *var);
void				push_env_back(t_env **head, char *value);

int					ft_export(char **args, t_env **env);
int					ft_unset(char **args, t_env **env);

void				free_command_list(t_cmd **cmd_list);
void				free_array(char **arr);

#endif