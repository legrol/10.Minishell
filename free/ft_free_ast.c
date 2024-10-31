/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:41:34 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/10/31 15:00:22 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * 
 * 
 */

void	ft_free_ast(t_ast *ast)
{
	t_ast	*temp;

	while (ast)
	{
		temp = ast;
		ast = ast->left;
		free(temp->value);
		free(temp);
	}
}
