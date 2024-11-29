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
 * This file will be one of the executor files:
 * 
 * void ft_exec_redir_out(t_minishell *minishell, t_ast *ast) we create a fork
 * to execute the command in the child and with fd we copy the std_out in the 
 * file, > should create a new file if not exist or trunc the existing one a 
 * fill with the new information.
 * 
 */

/**
 * The function "ft_exec_redir_out" handles output redirection for a shell 
 * command. It opens the specified file for writing, forks a child process, 
 * and redirects the output of the command to the file.
 * 
 * - The file is opened with the following flags:
 *   - `O_WRONLY`: Open the file in write-only mode.
 *   - `O_CREAT`: Create the file if it does not exist.
 *   - `O_TRUNC`: Truncate the file to zero length if it already exists.
 *   - The file permissions are set to `0644` for newly created files.
 * 
 * - In case of errors during file opening or process forking, the function 
 *   prints an error message and performs necessary cleanup.
 * 
 * - In the child process:
 *   - Redirects `STDOUT` to the file descriptor, so the command writes its 
 *     output to the file.
 *   - Closes the file descriptor.
 *   - Executes the left subtree of the AST (the actual command).
 *   - Exits with an error code if execution fails.
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


static void	ft_try_dup2_out(t_minishell *minishell, int fd)
{
	if (minishell->redout == -1)
	{
		dup2(fd, STDOUT_FILENO);
		minishell->redout = 1;
	}
}

static int	ft_contains_invalid_chars(const char *line)
{
	return (ft_strnstr(line, "\033[?2004h",ft_strlen(line)) != NULL || ft_strnstr(line, "\033[?2004h",ft_strlen(line)) != NULL);
}


static void	ft_process_heredoc_and_filter(t_ast *heredoc_ast, char *outfile)
{
	char	*input;
	int		out_fd;

	out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_fd < 0)
	{
		perror("Error abriendo archivo de salida");
		return;
	}
	while (1)
	{
		input = readline("> ");
		if (!input || ft_strcmp(input, heredoc_ast->right->value) == 0)
		{
			free(input);
			break;
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


void	ft_exec_redir_out(t_minishell *minishell, t_ast *ast)
{
	int		fd;
	pid_t	pid;

	if (ast->left && ast->left->type == TOKEN_REDIR_HEREDOC)
	{
		ft_process_heredoc_and_filter(ast->left, ast->right->value);
		return;
	}
	fd = open(ast->right->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_printf("Error: Open file");
		return;
	}
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
	ft_free_ast(ast);
	close(fd);
}

