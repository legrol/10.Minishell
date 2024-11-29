/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_redir_append.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:50:37 by pabromer          #+#    #+#             */
/*   Updated: 2024/11/29 15:17:45 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_exec_redir_append" handles the append redirection for 
 * commands. If the command is a heredoc, it processes the heredoc input and 
 * appends it to the specified file. For other commands, it forks a child 
 * process to execute the command with output appended to the file.
 * 
 * @param t_minishell *minishell	A pointer to the minishell structure that 
 * 									manages the execution state and redirections.
 * @param t_ast *ast				A pointer to the AST node representing the 
 * 									command with append redirection.
 * @return void
 * 
 * The function "ft_fork_and_execute_append" creates a child process to execute 
 * the left subtree of the AST. The standard output is redirected to the 
 * specified file descriptor, allowing the command's output to be appended to 
 * a file. The parent process waits for the child to finish.
 * 
 * @param t_minishell *minishell	A pointer to the minishell structure 
 * 									containing execution state information.
 * @param t_ast *ast				A pointer to the AST representing the 
 * 									command to be executed.
 * @param int fd					The file descriptor for appending output.
 * @return void
 * 
 * The function "ft_open_redir_append" opens a file in append mode. If the file 
 * does not exist, it creates the file. The file descriptor is returned for 
 * further operations.
 * 
 * @param const char *filename		The name of the file to open or create.
 * @return int						Returns the file descriptor if successful, 
 * 									or -1 if an error occurs.
 * 
 * The function "ft_process_heredoc_and_filter" processes a heredoc input, 
 * appending user input to the specified output file until the heredoc 
 * delimiter is encountered. It filters out lines with invalid characters.
 * 
 * @param t_ast *heredoc_ast		A pointer to the AST node representing the 
 * 									heredoc command and its delimiter.
 * @param char *outfile				The name of the file where the heredoc 
 * 									content will be appended.
 * @return void
 * 
 */

static void	ft_process_heredoc_and_filter(t_ast *heredoc_ast, char *outfile)
{
	char	*input;
	int		out_fd;

	out_fd = open(outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
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

static int	ft_open_redir_append(const char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd < 0)
		ft_printf("Error: Open file\n");
	return (fd);
}

static void	ft_fork_and_execute_append(t_minishell *minishell, \
t_ast *ast, int fd)
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

void	ft_exec_redir_append(t_minishell *minishell, t_ast *ast)
{
	int	fd;

	if (ast->left && ast->left->type == TOKEN_REDIR_HEREDOC)
	{
		ft_process_heredoc_and_filter(ast->left, ast->right->value);
		return ;
	}
	fd = ft_open_redir_append(ast->right->value);
	if (fd < 0)
		return ;
	ft_fork_and_execute_append(minishell, ast, fd);
	ft_free_ast(ast);
	close(fd);
}
