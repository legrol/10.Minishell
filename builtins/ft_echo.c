/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:36:47 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/10/30 12:23:16 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * 
 * FALTA liberar el split
*/

/*static int	ft_echo_only(t_minishell *minishell)
{
	char *trim;

	trim = ft_strtrim(minishell->line, " ");
	if (ft_strcmp(trim, "echo") == 0)
	{
		printf("\n");
		free(trim);
		return (1);
	}
	free(trim);
	return (0);
}*/

/*static void ft_print_echo(char *str, char c, t_minishell *minishell)
{
	char *trim;

	if (ft_strchr(str, '\''))
	{
		trim = ft_strtrim(str, "\'");
		if (ft_strcmp(trim, "$?") == 0)
			ft_printf("%i%c", minishell->exit, c);
		else 
			ft_printf("%s%c", trim, c);
	}
	else 
	{
		trim = ft_strtrim(str, "\"");
		if (ft_strcmp(trim, "$?") == 0)
			ft_printf("%i%c", minishell->exit, c);
		else 
			ft_printf("%s%c", trim, c);
	}
	minishell->exit = 0;
	free(trim);
}*/

void	ft_echo(t_ast *ast)
{
	int i;
	t_ast *temp;
	int f;

	f = 0;
	i = 0;
	temp = ast;
	while (ast)
	{
		if (i == 1 && ft_strcmp(ast->value, "-n") == 0)
			f = 1;
		i++;
		ast = ast->left;
	}
	ast = temp;
	if (i == 1)
	{
		printf("\n");
		return ;
	}	
	else if (i == 2 && f == 1)
	{
		printf("");
		return ;
	}
	ast = ast->left;
	if (f == 1)
		ast = ast->left;
	while(ast->left)
	{
		printf("%s ", ast->value);
		ast = ast->left;
	}
	printf("%s", ast->value);
	if (f == 0)
		printf("\n");
}
