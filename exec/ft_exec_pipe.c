/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:50:37 by pabromer          #+#    #+#             */
/*   Updated: 2024/11/24 12:59:48 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * This file will be one of the executor files:
 * 
 * 
 * void ft_exec_pipe(t_minishell *minishell, t_ast *ast) execute the pipes 
 * executing the left command in the pid1 y the right command in pid2.
 * 
 * static pid_t	ft_cmdexe_pid1(t_minishell *minishell, t_ast *ast, int *fd) 
 * duplicate the output to the writting file descriptor fd[1] and call 
 * ft_exec_ast for the left command in recursive mode.
 *  
 * static pid_t	ft_cmdexe_pid1(t_minishell *minishell, t_ast *ast, int *fd) 
 * duplicate the output to the reading file descriptor fd[0] and call 
 * ft_exec_ast for the right command in recursive mode. * 
 * 
 */

static pid_t	ft_cmdexe_pid1(t_minishell *minishell, t_ast *ast, int *fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_printf("Error making fork");
		close(fd[0]);
		close(fd[1]);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (fd[1] < 0)
		{
			ft_printf("Error opening file prueba");
			exit(EXIT_FAILURE);
		}
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		ft_exec_ast(minishell, ast->left);
		//ft_free_ast(ast);
		exit(EXIT_FAILURE);
	}
	return (pid);
}

static pid_t	ft_cmdexe_pid2(t_minishell *minishell, t_ast *ast, int *fd)
{
	pid_t	pid;

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
		ft_exec_ast(minishell, ast->right);
		//ft_free_ast(ast);
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void ft_exec_pipe(t_minishell *minishell, t_ast *ast)
{
	int		fd[2];
	int		status;
	pid_t	pid1;
	pid_t	pid2;

	pid1 = 0;
	if (pipe(fd) == -1)
	{
		ft_printf("Error making pipe");
		return ;
	}
	pid1 = ft_cmdexe_pid1(minishell, ast, fd);
	pid2 = ft_cmdexe_pid2(minishell, ast, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	ft_free_ast(ast);
	//ft_free_tokens(minishell->tokens);
}








