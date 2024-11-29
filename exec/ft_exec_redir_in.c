/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_redir_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:50:37 by pabromer          #+#    #+#             */
/*   Updated: 2024/11/27 16:38:35 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * This file will be one of the executor files:
 * 
 * void ft_exec_redir_out(t_minishell *minishell, t_ast *ast) we create a fork 
 * to execute the command in the child and with fd we copy the std_out in the 
 * file, > should create a new file if not exist or trunc the existing one a 
 * fill with the new information.
 * 
 */

/**
 * The function "ft_exec_redir_in" handles input redirection for a shell 
 * command. It opens the specified file for reading, forks a child process, 
 * and redirects the input of the command from the file.
 * 
 * - The file is opened with the following flag:
 *   - `O_RDONLY`: Open the file in read-only mode.
 * 
 * - In case of errors during file opening or process forking, the function 
 *   prints an error message and performs necessary cleanup.
 * 
 * - In the child process:
 *   - Redirects `STDIN` to the file descriptor, so the command reads input 
 *     from the file.
 *   - Closes the file descriptor.
 *   - Executes the left subtree of the AST (the actual command).
 *   - Exits with success status if execution is successful.
 * 
 * - The parent process waits for the child process to complete execution 
 *   and frees memory resources.
 * 
 * @param t_minishell *minishell	A pointer to the shell's state structure, 
 *									used for managing execution and state.
 * 
 * @param t_ast *ast				A pointer to the AST structure representing 
 *									the redirection operation and the command 
 *									to be executed.
 * 
 * @return void						This function does not return a value. 
 * 
 */

void	ft_error_make_fork(int fd)
{
	ft_printf("Error making fork");
	close(fd);
}

static void	ft_try_dup2_in_2(t_minishell *minishell, int fd)
{
	if (minishell->redin == -1)
	{
		dup2(fd, STDIN_FILENO);
		minishell->redin = 1;
	}
}

void	ft_exec_redir_in(t_minishell *minishell, t_ast *ast)
{
	int		fd;
	pid_t	pid;

	fd = open(ast->right->value, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error: Open file");
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		ft_error_make_fork(fd);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		ft_try_dup2_in_2(minishell, fd);
		close(fd);
		ft_exec_ast(minishell, ast->left);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, NULL, 0);
	ft_free_ast(ast);
	close(fd);
}
