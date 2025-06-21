/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 09:23:32 by ael-krai          #+#    #+#             */
/*   Updated: 2025/06/21 11:53:25 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./gnl/get_next_line.h"
# include "./libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <unistd.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SUCCESS 0
# define FAILURE 1
# define NOTFOUND 127

# define UNEXPECTED "syntax error near unexpected "
# define UNEXPECTED_TOKEN "syntax error near unexpected token "

extern int	g_exit_code;

typedef struct s_fd
{
	int	pipefd[2];
	int	fdin;
	int	fdout;
}	t_fd;

typedef struct s_env
{
	int				exit_code;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef enum e_type
{
	WORD,
	PIPE,
	IN,
	OUT,
	APPEND,
	HEREDOC,
	AND,
	OR
}	t_type;

typedef struct s_token
{
	t_type			type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**args;
	char			**outfile;
	char			**heredoc;
	char			*infile;
	char			*cmd_path;
	pid_t			pid;
	int				pipe;
	int				append;
	struct s_cmd	*next;
}	t_cmd;

// ----------------[built_ins]------------------
// builtin_utils
char	*get_var_name(char *var);
char	*var_value(char *var);
// env
char	*get_env_value(t_env *env, const char *key);

// ----------------[env]------------------------
// env
void	push_env(t_env **head, char *value);
int		init_env(t_env **env, char **envp);
void	reset_terminal(void);
// shell level
int		env_size(t_env *env);
char	**env_to_str(t_env *env);
void	handle_empty_env(t_env **env);
void	increment_shell(t_env **env);

// ----------------[execution]------------------
// error_handler
void	init_fds(t_fd *fd);

// ----------------[main]-----------------------
// signals
void	signal_handler(int signal);
void	handle_signals(void);

// ----------------[parsing]--------------------
// ambiguous
int		ambiguous_redirect(char *line, t_env *env);
// errors
int		is_operator(char *line, int i);
int		check_semicolon(char *line);
char	*extract_filename(char *line);
int		pipe_errors(char *line);
int		redirect_errors(char *line, int i, char *file);
// ft_addstr
char	**ft_addstr(char **arr, char *str);
// helper
void	skip_dollar(char *line, int *i);
void	process_env_var(char *line, int *i, t_env **env, char **result);
char	*trim_env(char *s);
// parsing
int		open_quotes(char *line);
t_cmd	*ft_parse(char *line, t_env **env);
t_type	get_type(char *line, int *i);
// redirection
void	parse_tokens(t_token *tokens, t_cmd **cmds);
t_cmd	*handle_pipe(t_cmd *cmd, t_cmd **cmds);
void	update_redirection(char ***list, t_token *current);
void	process_redirection(t_cmd *cmd, t_token *current);
// tokenizer
void	process_and_add_token(t_token **token, t_env **env, char *line, int *i);
void	process_word(char *line, int *i, t_env **env, char **value);
void	expand_env(char *line, int *i, t_env **env, char **result);
char	*handle_quotes(char *line, int *i, t_env **env, char quote);
void	handle_char(char c, char **value);
// utils
t_cmd	*tokenize_line(char *line, t_env **env);
char	*add_result(char *result, char *tmp);
t_cmd	*init_cmd(void);

// ----------------[utils]----------------------
// list_utils
t_token	*create_node(t_type type, char *value);
void	push_cmd(t_cmd **head, t_cmd *node);
void	push_back(t_token **head, t_type type, char *value);
// free_mem
void	free_token(t_token **token);
void	free_env(t_env **env);
void	free_cmd(t_cmd **cmd);
void	free_cmd_fields(t_cmd *cmd);
void	free_array(char **arr);

#endif