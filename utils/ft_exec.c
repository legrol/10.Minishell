/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:50:37 by pabromer          #+#    #+#             */
/*   Updated: 2024/11/08 16:35:31 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_exec(t_minishell *minishell, t_ast *ast)
{
	if (ft_strcmp(ast->value, "cd") == 0)
		ft_cd(minishell, ast);
	else if (ft_strcmp(ast->value, "env") == 0)
		ft_env(minishell);
	else if (ft_strcmp(ast->value, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(ast->value, "echo") == 0)
		ft_echo(minishell, ast);
	else if (ft_strcmp(ast->value, "export") == 0)
		ft_export(minishell, ast);
	else if (ft_strcmp(ast->value, "unset") == 0)
		ft_unset(minishell, ast);
	else if (ft_strcmp(ast->value, "exit") == 0)
		return 1;
	else
		ft_cmdexe(minishell, ast);
	return 0;
}

static pid_t	ft_cmdexe_pid1(t_minishell *minishell, t_ast *ast, int *fd)
{
	char	**arg;
	char	*cmd;
	pid_t	pid;

	//ft_printf("Estoy ejecutando %s ------- \n", ast->value);
	if (pid < 0)
	{
		ft_printf("Error making fork");
		close(fd[0]);
		close(fd[1]);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(cmd, arg, minishell->envp);
		perror("execve cmd2:");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

static pid_t	ft_cmdexe_pid2(t_minishell *minishell, t_ast *ast, int *fd)
{
	char	**arg;
	char	*cmd;
	pid_t	pid;

	//ft_printf("Estoy ejecutando %s ------- \n", ast->value);
	pid = fork();
	if (pid == -1)
	{
		ft_printf("Error making fork");
		close(fd[0]);
		close(fd[1]);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(cmd, arg, minishell->envp);
		perror("execve cmd2:");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void ft_exec_pipe(t_minishell *minishell, t_ast *ast)
{
	int fd[2];
	pid_t pid1;
	pid_t pid2;
	int status;

	if(pipe(fd) == -1)
	{
		ft_printf("Error making pipe");
		return ;
	}
	pid1 = ft_cmdexe_pid1(minishell, ast->left, fd);
	pid2 = ft_cmdexe_pid2(minishell, ast->right, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &status, 0);
    waitpid(pid2, &status, 0);
}


