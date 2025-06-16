/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnahli <mnahli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:34:25 by ael-krai          #+#    #+#             */
/*   Updated: 2025/06/16 11:54:43 by mnahli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <dirent.h>
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

# define NOTFOUND 127
# define FAILURE 1
# define SUCCESS 0

int					g_exit_code;

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_cmd
{
	char			**args;
	char			**heredoc;
	char 			*cmd_path; // 2 stars or one star
	pid_t			pid;
	char			*infile;
	char			**outfile;
	int				pipe;
	int				append;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_fd
{
	int				pipefd[2];
	int				fdin;
	int				fdout;
}					t_fd;

// ------------------------------ EXECUTION ------------------------------ //
// env
int					env_init(t_env **env, char **envp);
void				increment_shell_lvl(t_env **env);

// builtin check
int					is_builtin(char *command);
int					exec_bltin(t_cmd *current, t_env **env, t_fd *fd);
void				exec_builtin(char **args, t_env **env);

// builtin exit utils
void				ft_exit(char **args, t_cmd **cmds, t_env **env, t_fd *fd);

// env utils
char				*get_env_value(t_env *env, const char *key);
char				*get_var_name(char *var);
char				*get_var_value(char *var);
int					is_valid_env_var_name(char *var);

// redir open
int					open_redir(t_cmd *current, t_fd *fd);
int					dup_stdout(t_fd *fd, int newfd);
int					dup_stdin(t_fd *fd, int newfd);

// cmd path utils
char				**get_path(char **envp);
int					resolve_cmd_path(char **envp, t_cmd *cmd);

// heredoc
int					ft_heredoc(char *delimiter, t_env *env);

// cmd helper
void				exit_func(t_fd *fd, int status);
void				cmd_files_handler(t_cmd *cmd, t_fd *fd);
int					check_is_dir(char *cmd);
int					var_in_line(char *delimiter, char *line);

// signal handler
void				setup_signals(void);
void				reset_terminal(void);
void				signal_heredoc(int sig);

// fds utils
void				close_fds(t_fd *fd);
void				init_fds(t_fd *fd);

// expansion
void				expand_variables(t_env *env, char *line, int fd);

// memory cleanup
void				free_command_list(t_cmd **cmd_list);
void				free_array(char **arr);
void				free_env(t_env **env);

#endif