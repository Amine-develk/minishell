#include "minishell.h"

int	is_operator(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return(0);
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	if (!cmd)
		return ;
	while (*cmd)
	{
		tmp = *cmd;
		(*cmd) = (*cmd)->next;
		free(tmp);
	}
}

int	check_parsing(char *str)
{
	int	i;
	int	d;
	int	s;

	i = 0;
	d = 0;
	s = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			d++;
		else if (str[i] == '\'')
			s++;
		i++;
	}
	if (str[i - 1] == '|' || str[i - 1] == '>' || str[i - 1] == '<'
		|| str[0] == '|' || d % 2 != 0 || s % 2 != 0)
		return (1);
	return (0);
}

t_cmd	*create_cmd(char *str)
{
	t_cmd	*cmd;

	if (!(cmd = malloc(sizeof(t_cmd))))
		return (NULL);
	cmd->value = str;
	cmd->next = NULL;
	return (cmd);
}

void	push_cmd(t_cmd **lst, t_cmd *cmd)
{
	t_cmd	*tmp;

	if (!cmd || !lst)
		return ;
	if (!*lst)
	{
		*lst = cmd;
		return ;
	}
	tmp = (*lst);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = cmd;
}
