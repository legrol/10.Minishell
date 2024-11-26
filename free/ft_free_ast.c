/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:41:34 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/26 16:53:16 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_free_ast" recursively frees the memory allocated for an 
 * Abstract Syntax Tree (AST). It traverses the tree in a post-order manner, 
 * ensuring that the left and right subtrees are freed before freeing the 
 * current node.
 * 
 * - If the input `ast` is `NULL`, the function immediately returns, ensuring 
 *   safe handling of empty trees.
 * - Recursively frees the left and right child nodes of the AST.
 * - Frees the memory allocated for the `value` field of the current node.
 * - Frees the memory allocated for the node itself.
 * 
 * This function ensures that all nodes and associated data in the AST are 
 * properly deallocated, preventing memory leaks.
 * 
 * @param t_ast *ast	A pointer to the root of the Abstract Syntax Tree 
 *						to be freed.
 * 
 * @return void			This function does not return a value.
 * 
 */

void	ft_free_ast(t_ast *ast)
{
	if (!ast)
		return ;
	ft_free_ast(ast->left);
	ft_free_ast(ast->right);
	free(ast->value);
	free(ast);
}

void	ft_free_ast_left(t_ast *ast)
{
	if (!ast)
		return ;
	ft_free_ast(ast->left);
	free(ast->value);
	free(ast);
}
