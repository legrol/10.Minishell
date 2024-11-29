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


static int	ft_try_dup2_in(t_minishell *minishell, int fd)
{
	if (minishell->redin == -1)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		minishell->redin = 1;
        return (0);
	}
    return (-1);
}

void	ft_exec_redir_heredoc(t_minishell *minishell, t_ast *ast)
{
    char *input;
    int fd[2];
    pid_t pid;
    int stdin_copy;

    if (!ast || !ast->right || !ast->right->value)
    {
        ft_printf("Error: Heredoc not valid\n");
        return;
    }
    if (pipe(fd) == -1)
    {
        perror("Error: Cant create pipe for heredoc");
        return;
    }
    stdin_copy = dup(STDIN_FILENO);
    if (stdin_copy == -1)
    {
        perror("Error saving STDIN");
        close(fd[0]);
        close(fd[1]);
        return;
    }
    pid = fork();
    if (pid == -1)
    {
        perror("Error: Fork fail in heredoc");
        close(fd[0]);
        close(fd[1]);
        close(stdin_copy);
        return;
    }
    if (pid == 0)
    {
        close(fd[0]);
        while (1)
        {
            input = readline("> ");
            if (!input || ft_strcmp(input, ast->right->value) == 0)
            {
                free(input);
                break;
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
    close(fd[1]);
    if (ft_try_dup2_in(minishell,fd[0]) == -1)
    {
        perror("Error duplicating fd in heredoc");
        close(fd[0]);
        close(stdin_copy);
        return;
    }
    close(fd[0]);
    waitpid(pid, NULL, 0);
    ft_exec_ast(minishell, ast->left);
    if (ft_try_dup2_in(minishell, stdin_copy) == -1)
    {
        perror("Error restoring STDIN");
    }
    close(stdin_copy);
}

