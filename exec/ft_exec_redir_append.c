/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_redir_append.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:50:37 by pabromer          #+#    #+#             */
/*   Updated: 2024/11/21 15:12:52 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * This file will be one of the executor files:
 * 
 * void ft_exec_redir_out(t_minishell *minishell, t_ast *ast) we create a fork to execute the command in the child and with fd we copy the std_out in the file, > should create a new file if not exist
 * or trunc the existing one a fill with the new information.
 * 
 */

void	ft_exec_redir_append(t_minishell *minishell, t_ast *ast)
{
	int fd;
	pid_t pid;

	fd = open(ast->right->value, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd < 0)
	{
		ft_printf("Error: Open file");
		return ;
	}
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
		//ft_free_ast(ast);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, NULL, 0);
	ft_free_ast(ast);
	ft_free_tokens(minishell->tokens);
	close(fd);
}







