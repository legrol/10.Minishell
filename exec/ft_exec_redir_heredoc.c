/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_redir_append.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:50:37 by pabromer          #+#    #+#             */
/*   Updated: 2024/11/24 12:59:59 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_exec_redir_heredoc" handles input redirection for the shell
 * when a heredoc operation is required. It opens the file specified in the 
 * Abstract Syntax Tree (AST) for reading, creates a child process to handle
 * execution, and redirects the output to the specified file descriptor.
 * 
 * @param t_minishell *minishell	A pointer to the `t_minishell` structure
 *									that contains the shell's state, such as
 *									environment variables, configuration, and
 *									helper functions used for execution.
 * 
 * @param t_ast *ast				A pointer to the `t_ast` structure, which
 *									represents a node in the Abstract Syntax
 *									Tree. This node contains the command or
 *									redirection operation to be executed.
 *									- `ast->right` points to the node
 *									  containing the file path for the heredoc.
 *									- `ast->left` points to the command to be
 *									  executed after setting up the 
 *									  redirection.
 * 
 */

void	ft_exec_redir_heredoc(t_minishell *minishell, t_ast *ast)
{
	int		fd;
	pid_t	pid;

	fd = open(ast->right->value, O_RDONLY);
	if (fd < 0)
		return ((void)ft_printf("Error: Open file"));
	pid = fork();
	if (pid == -1)
	{
		ft_printf("Error making fork");
		close(fd);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
		ft_exec_ast(minishell, ast->left);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, NULL, 0);
	ft_free_ast(ast);
	close(fd);
}







