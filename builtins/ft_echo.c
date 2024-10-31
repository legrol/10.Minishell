/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:36:47 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/10/30 12:56:14 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * 
 * FALTA liberar el split
*/

static int ft_echo_init(t_ast *ast)
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
		return (-1+(0*printf("\n")));
	else if (i == 2 && f == 1)
		return (-1+(0*printf("")));
	return (f);
}

void	ft_echo(t_ast *ast)
{
	t_ast *temp;
	int f;

	f = 0;
	temp = ast;
	f = ft_echo_init(ast);
	if (f == -1)
		return;
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
	ast = temp;
}
