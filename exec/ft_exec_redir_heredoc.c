/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_redir_heredoc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:50:37 by pabromer          #+#    #+#             */
/*   Updated: 2024/11/29 15:20:06 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_exec_redir_heredoc" handles the execution of a heredoc 
 * redirection.
 * It creates a pipe, forks a child process to handle input collection, and 
 * manages the parent's responsibilities such as executing the left-hand side
 * of the AST.
 * 
 * @param t_minishell *minishell	A pointer to the minishell structure
 * 									containing the state.
 * @param t_ast *ast				A pointer to the AST node for the heredoc 
 * 									operation.
 * @return 							void
 * 
 * The function "ft_handle_heredoc_parent" runs in the parent process of a 
 * heredoc operation.
 * It duplicates the pipe's read-end to STDIN, waits for the child process to 
 * finish, and then executes the left side of the AST. After execution, it 
 * restores the original STDIN.
 * 
 * @param t_minishell *minishell	A pointer to the minishell structure 
 * 									containing the state.
 * @param t_ast *ast				A pointer to the AST node for the heredoc 
 * 									operation.
 * @param int *fd					Array of two file descriptors for the pipe.
 * @param int stdin_copy			The saved copy of STDIN to be restored 
 * 									later.
 * @return 							void
 * 
 * The function "ft_handle_heredoc_child" runs in the child process of a 
 * heredoc operation.
 * It repeatedly reads input from the user until the input matches the 
 * specified delimiter or an end-of-file condition occurs. Valid input is 
 * written to the write-end of the pipe.
 * 
 * @param t_ast *ast				A pointer to the AST node that contains the
 * 									heredoc delimiter.
 * @param int *fd					Array of two file descriptors for the pipe.
 * @return 							void
 * 
 * The function "ft_cleanup_pipe" closes the provided pipe file descriptors 
 * and, optionally, a copy of the standard input descriptor. It also prints 
 * the specified error message using `perror`.
 * 
 * @param int *fd					Array of two file descriptors for the pipe
 * 									to be closed.
 * @param int stdin_copy			The saved copy of STDIN to be closed (-1 if
 * 									not applicable).
 * @param char *error_message		The error message to be printed via 
 * 									`perror`.
 * @return 							void
 * 
 * The function "ft_validate_heredoc_ast" checks if the given Abstract Syntax 
 * Tree (AST) for a heredoc operation is valid. It ensures that the AST and its
 * `right` node, as well as the `value` field of the `right` node, are not 
 * null.
 * 
 * @param t_ast *ast				A pointer to the AST node to be validated.
 * @return bool						Returns true if the AST is valid; 
 * 									otherwise, prints an error message and 
 * 									returns false.
 * 
 */

bool	ft_validate_heredoc_ast(t_ast *ast)
{
	if (!ast || !ast->right || !ast->right->value)
	{
		ft_printf("Error: Heredoc not valid\n");
		return (false);
	}
	return (true);
}

void	ft_cleanup_pipe(int *fd, int stdin_copy, char *error_message)
{
	perror(error_message);
	close(fd[0]);
	close(fd[1]);
	if (stdin_copy != -1)
		close(stdin_copy);
}

void	ft_handle_heredoc_child(t_ast *ast, int *fd)
{
	char	*input;

	signal(SIGINT, SIG_DFL);
	close(fd[0]);
	while (1)
	{
		input = readline("> ");
		if (!input || ft_strcmp(input, ast->right->value) == 0)
		{
			free(input);
			break ;
		}
		if (*input != '\0')
		{
			write(fd[1], input, ft_strlen(input));
			write(fd[1], "\n", 1);
		}
		free(input);
	}
	close(fd[1]);
	_exit(EXIT_SUCCESS);
}

void	ft_handle_heredoc_parent(t_minishell *minishell, t_ast *ast, \
int *fd, int stdin_copy)
{
	int	status;

	close(fd[1]);
	waitpid(-1, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		g_signals.exit = EX_SIGINT;
		close(fd[0]);
		close(stdin_copy);
		return ;
	}
	if (ft_try_dup2_in(minishell, fd[0]) == -1)
	{
		perror("Error duplicating fd in heredoc");
		close(fd[0]);
		close(stdin_copy);
		return ;
	}
	close(fd[0]);
	ft_exec_ast(minishell, ast->left);
	if (ft_try_dup2_in(minishell, stdin_copy) == -1)
		perror("Error restoring STDIN");
	close(stdin_copy);
}

void	ft_exec_redir_heredoc(t_minishell *minishell, t_ast *ast)
{
	int		fd[2];
	int		stdin_copy;
	pid_t	pid;

	if (!ft_validate_heredoc_ast(ast))
		return ;
	if (pipe(fd) == -1)
	{
		perror("Error: Can't create pipe for heredoc");
		return ;
	}
	g_signals.in_heredoc = 1;
	stdin_copy = dup(STDIN_FILENO);
	if (stdin_copy == -1)
		return (ft_cleanup_pipe(fd, -1, "Error saving STDIN"));
	pid = fork();
	if (pid == -1)
		return (ft_cleanup_pipe(fd, stdin_copy, "Error: Fork failed \
		in heredoc"));
	g_signals.pid = pid;
	if (pid == 0)
		ft_handle_heredoc_child(ast, fd);
	ft_handle_heredoc_parent(minishell, ast, fd, stdin_copy);
	g_signals.pid = 0;
	g_signals.in_heredoc = 0;
}
