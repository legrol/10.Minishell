/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:50:37 by pabromer          #+#    #+#             */
/*   Updated: 2024/11/26 16:57:11 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * *********************************************************************
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
 * ft_exec_ast for the right command in recursive mode. 
 * *********************************************************************
 * 
 */

/**
 * The function "ft_exec_pipe" handles the execution of a pipeline in the 
 * shell.
 * It creates a pipe, forks two child processes for the left and right sides 
 * of the pipeline, and connects their input and output via the pipe.
 * 
 * - The pipe is used to pass the output of the left command as input to the 
 *   right command.
 * - After creating the pipe and forking the child processes:
 *   - The parent process closes both ends of the pipe.
 *   - It waits for both child processes to finish using `waitpid`.
 * - Frees the AST structure after execution.
 * 
 * @param t_minishell *minishell	A pointer to the shell's state structure, 
 *									used for managing execution and state.
 * 
 * @param t_ast *ast				A pointer to the AST structure 
 * 									representing the pipeline to be executed.
 * 
 * @return void						This function does not return a value.
 * 
 * The function "ft_cmdexe_pid2" executes the right side of a pipeline in a child
 * process. It creates a new process using `fork`, redirects the input of the
 * process to the read end of a pipe, and executes the right side of the AST.
 * 
 * - If `fork` fails, it prints an error message, closes the pipe, and exits 
 *   the program with an error code.
 * - In the child process:
 *   - Redirects `STDIN` to the pipe's read end.
 *   - Closes both ends of the pipe.
 *   - Executes the right subtree of the AST.
 * 
 * @param t_minishell *minishell	A pointer to the shell's state structure, 
 *									used for executing commands.
 * 
 * @param t_ast *ast				A pointer to the AST structure containing 
 *									the right side of the command pipeline.
 * 
 * @param int *fd					A pointer to an array representing the pipe 
 *									file descriptors (`fd[0]` for reading, 
 *									`fd[1]` for writing).
 * 
 * @return pid_t					The process ID of the created child 
 * 									process.
 * 
 * The function "ft_cmdexe_pid1" executes the left side of a pipeline in a 
 * child process. It creates a new process using `fork`, redirects the output
 * of the process to the write end of a pipe, and executes the left side of the
 * abstract syntax tree (AST).
 * 
 * - If `fork` fails, it prints an error message, closes the pipe, and exits 
 *   the program with an error code.
 * - In the child process:
 *   - Redirects `STDOUT` to the pipe's write end.
 *   - Closes both ends of the pipe.
 *   - Executes the left subtree of the AST.
 * 
 * @param t_minishell *minishell	A pointer to the shell's state structure, 
 *									used for executing commands.
 * 
 * @param t_ast *ast				A pointer to the AST structure containing 
 *									the left side of the command pipeline.
 * 
 * @param int *fd					A pointer to an array representing the pipe 
 *									file descriptors (`fd[0]` for reading, 
 *									`fd[1]` for writing).
 * 
 * @return pid_t					The process ID of the created child process.
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

void	ft_exec_pipe(t_minishell *minishell, t_ast *ast)
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
}
