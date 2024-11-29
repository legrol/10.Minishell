/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_redir_out.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:50:37 by pabromer          #+#    #+#             */
/*   Updated: 2024/11/29 15:17:54 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_exec_redir_out" handles output redirection for commands
 * represented in the AST. It manages heredoc input redirections or writes
 * directly to a file. For non-heredoc commands, it forks a child process to 
 * execute the command with redirected output.
 * 
 * @param t_minishell *minishell	A pointer to the minishell structure that
 * 									manages state and execution.
 * @param t_ast *ast				A pointer to the AST node representing the
 * 									redirection command.
 * @return void
 * 
 * The function "ft_fork_and_execute" forks a child process to execute the 
 * left subtree of the AST. The output is redirected to the provided file 
 * descriptor. The parent process waits for the child process to finish.
 * 
 * @param t_minishell *minishell	A pointer to the minishell structure 
 * 									containing state information.
 * @param t_ast *ast				A pointer to the AST representing the 
 * 									command to be executed.
 * @param int fd					The file descriptor to which output is 
 * 									redirected.
 * @return void
 * 
 * The function "ft_open_redir_out" opens or creates a file for writing, 
 * truncating its content if it already exists. It returns the file 
 * descriptor or prints an error message if the operation fails.
 * 
 * @param const char *filename		The name of the file to be opened.
 * @return int						Returns the file descriptor if successful,
 * 									or -1 if an error occurs.
 * 
 * The function "ft_process_heredoc_and_filter" processes a heredoc input, 
 * allowing the user to input multiple lines until the specified delimiter 
 * is encountered. Lines containing invalid characters are filtered out, 
 * and valid input is written to the specified output file.
 * 
 * @param t_ast *heredoc_ast		A pointer to the AST node representing the
 * 									heredoc command and its delimiter.
 * @param char *outfile				The name of the file where heredoc content 
 * 									will be written.
 * 
 */

static void	ft_process_heredoc_and_filter(t_ast *heredoc_ast, char *outfile)
{
	char	*input;
	int		out_fd;

	out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_fd < 0)
	{
		perror("Error abriendo archivo de salida");
		return ;
	}
	while (1)
	{
		input = readline("> ");
		if (!input || ft_strcmp(input, heredoc_ast->right->value) == 0)
		{
			free(input);
			break ;
		}
		if (!ft_contains_invalid_chars(input))
		{
			write(out_fd, input, ft_strlen(input));
			write(out_fd, "\n", 1);
		}
		free(input);
	}
	close(out_fd);
}

static int	ft_open_redir_out(const char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		ft_printf("Error: Open file\n");
	return (fd);
}

static void	ft_fork_and_execute(t_minishell *minishell, t_ast *ast, int fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_error_make_fork(fd);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		ft_try_dup2_out(minishell, fd);
		close(fd);
		ft_exec_ast(minishell, ast->left);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, NULL, 0);
}

void	ft_exec_redir_out(t_minishell *minishell, t_ast *ast)
{
	int	fd;

	if (ast->left && ast->left->type == TOKEN_REDIR_HEREDOC)
	{
		ft_process_heredoc_and_filter(ast->left, ast->right->value);
		return ;
	}
	fd = ft_open_redir_out(ast->right->value);
	if (fd < 0)
		return ;
	ft_fork_and_execute(minishell, ast, fd);
	ft_free_ast(ast);
	close(fd);
}
