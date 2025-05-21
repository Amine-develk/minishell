#include <stdio.h>
#include "../../includes/minishell.h"

char	**get_path(char **envp)
{
	char	**path;
	int 	i;

	if (!envp)
		return (NULL);
	i = 0;
	while(envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			path = ft_split(envp[i] + 5, ':');
			if (!path)
				return (NULL);
			return (path);
		}
		i++;
	}
	return (NULL);
}

int main(int ac, char **av, char **envp)
{
	(void)ac, (void)av;
	char **path = get_path(envp);
	if (!path)
		return (0);
	int i = 0;
	while (path[i])
	{
		printf("%s\n", path[i]);
		i++;
	}
	return 0;
}
