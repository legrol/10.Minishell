/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:36:47 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/04 12:40:49 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * 
 * FALTA liberar el split
*/
static void	ft_expand_echo(t_minishell *minishell, t_ast *ast)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split_m(ast->value, '$');
	while(split[i])
	{
		if(split[i][0] == '?')
			ft_printf("%i%s", minishell->exit, ft_strchr_exp(split[i], '?'));
		else if(ft_strchr(split[i], '?'))
			ft_printf("%s", ft_strchr(split[i], '?'));
		else if (ft_find_dir(minishell, split[i]))
			ft_printf("%s", ft_find_dir(minishell, split[i]));
		free(split[i]);
		i++;
	}
	ft_printf(" ");
	free(split);
}

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

void	ft_echo(t_minishell *minishell, t_ast *ast)
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
	while(ast)
	{
		if (ft_strchr(ast->value, '$'))
			ft_expand_echo(minishell, ast);
		else
			ft_printf("%s ", ast->value);
		ast = ast->left;
	}
	if (f == 0)
		ft_printf("\n");
	minishell->exit = 0;
	ast = temp;
}
