/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:50:37 by pabromer          #+#    #+#             */
/*   Updated: 2024/11/13 11:52:45 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * This file will be one of the executor files:
 * 
 * int ft_exec(t_minishell *minishell, t_ast *ast) executes the builtints or the commands in the PATH.
 * 
 * void ft_exec_ast(t_minishell *minishell, t_ast *ast) identifies the kind of token an call to the proper function.
 * 
 * void ft_exec_pipe(t_minishell *minishell, t_ast *ast) execute the pipes executing the left command in the pid1 y the right command in pid2.
 * 
 * static pid_t	ft_cmdexe_pid1(t_minishell *minishell, t_ast *ast, int *fd) duplicate the output to the writting file descriptor fd[1] and call ft_exec_ast for the left command in recursive mode.
 *  
 * static pid_t	ft_cmdexe_pid1(t_minishell *minishell, t_ast *ast, int *fd) duplicate the output to the reading file descriptor fd[0] and call ft_exec_ast for the right command in recursive mode.
 * 
 */

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

void ft_exec_ast(t_minishell *minishell, t_ast *ast)
{
    if (!ast)
        return ;
    if (ast->type == TOKEN_COMMAND)
        ft_exec(minishell, ast);
    else if (ast->type == TOKEN_PIPE)
        ft_exec_pipe(minishell, ast);
}
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
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		ft_exec_ast(minishell, ast->left);
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
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void ft_exec_pipe(t_minishell *minishell, t_ast *ast)
{
	int fd[2];
	pid_t pid1 = 0;
	pid_t pid2 = 0;
	int status;

	if(pipe(fd) == -1)
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
}







