/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdexe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:22:00 by pabromer          #+#    #+#             */
/*   Updated: 2024/10/18 11:35:02 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_cmd_action(char **path, char *arg)
{
	int		i;
	char	*cmd;

	i = 0;
	while (path[i])
	{
		cmd = ft_strjoin(path[i], arg);
		if (access(cmd, X_OK) == 0)
			return (cmd);
		free (cmd);
		cmd = NULL;
		i++;
	}
	return (NULL);
}

void	ft_cmdexe(t_minishell *minishell)
{
	char	**arg;
	char	*cmd;
	char	**path;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork fallo");
		exit (EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		path = ft_path(minishell);
		arg = ft_split(minishell->line, ' ');
		cmd = ft_cmd_action(path, arg[0]);
		execve(cmd, arg, NULL);
		perror("execve cmd2:");
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0);
}
