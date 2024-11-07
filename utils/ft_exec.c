/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:50:37 by pabromer          #+#    #+#             */
/*   Updated: 2024/11/07 16:22:21 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		ft_cmdexe(minishell);
	return 0;
}

/*void ft_exec_pipe(t_minishell *minishell, t_ast *ast)
{
	int fd[2];

	if(pipe(fd) == -1)
	{
		ft_printf("Error making pipe");
		return ;
	}
	
}*/


