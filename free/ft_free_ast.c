/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:41:34 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/26 10:43:28 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * 
 * 
 */

void	ft_free_ast(t_ast *ast)
{
	if(!ast)
		return ;
	ft_free_ast(ast->left);
	ft_free_ast(ast->right);
	free(ast->value);
	free(ast);
}

void	ft_free_ast_left(t_ast *ast)
{
	if(!ast)
		return ;
	ft_free_ast(ast->left);
	//ft_free_ast(ast->right);
	free(ast->value);
	free(ast);
}
