/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdexe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:22:00 by pabromer          #+#    #+#             */
/*   Updated: 2024/11/25 16:56:04 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Buscar y ejecutar el ejecutable correcto (basado en la variable PATH o mediante el
uso de rutas relativas o absolutas). FALTA EL USO DE VARIABLES RELATIVAS O ABSOLUTAS
 * 
*/

#include "../includes/minishell.h"

static void free_path(char **path)
{
	int	i;

	i = 0;
	while(path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

char	*ft_cmd_action(char **path, char *arg)
{
	int		i;
	char	*cmd;
	char	*temp;

	temp = ft_strtrim(arg, ".");
	i = 0;
	while (path[i])
	{
		cmd = ft_strjoin(path[i], temp);
		if (access(cmd, X_OK) == 0)
		{
			free(temp);
			return (cmd);
		}
		free (cmd);
		cmd = NULL;
		i++;
	}
	free(temp);
	if (access(arg, X_OK) == 0)
		return (free_path(path), ft_strdup(arg));
	free_path(path);
	return (NULL);
}

char *ft_cmd_maker(t_minishell *minishell, t_ast *ast)
{
	char	**path;
	char	*cmd;

	path = ft_path(minishell);
	cmd = ft_cmd_action(path, ast->value);
	return (cmd);
}

char **ft_arg_maker(t_ast *ast)
{
	char	**arg;
	t_ast	*temp;
	int		i;

	i = 0;
	temp = ast;
	while(ast)
	{
		i++;
		ast = ast->left;
	}
	ast = temp;
	arg = (char **)malloc((i+1)*sizeof(char *));
	if (!arg)
		return NULL;
	i = 0;
	while(ast)
	{
		arg[i] = ft_strdup(ast->value);
		ast = ast->left;
		i++;
	}
	arg[i] = NULL;
	ast = temp;
	return (arg);
}

void	ft_cmdexe(t_minishell *minishell, t_ast *ast)
{
	char	**arg;
	char	*cmd;
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
		arg = ft_arg_maker(ast);
		cmd = ft_cmd_maker(minishell, ast);
		execve(cmd, arg, minishell->envp);
		perror("execve cmd2:");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid ,&status, 0);
		//ft_free_ast(ast);
		minishell->exit = WEXITSTATUS(status);
	}
}


