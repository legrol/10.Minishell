/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-28 12:49:24 by rdel-olm          #+#    #+#             */
/*   Updated: 2024-11-28 12:49:24 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_ast_redir_in" creates a node for input redirection (`<`) in
 * the AST.
 * 
 * - Validates the current token and the following tokens for correctness.
 * - Creates a redirection node, assigns the left subtree, and constructs the 
 *   right subtree using `ft_ast_left`.
 * 
 * @param t_ast *ltree				The left subtree of the redirection node.
 * @param t_minishell *minishell	The shell's state structure containing the 
 * 									token list.
 * 
 * @return t_ast*					A pointer to the input redirection node in
 * 									the AST.
 * 
 * The function "ft_ast_pipe" creates a node for a pipe (`|`) operation in the 
 * AST.
 * 
 * - Ensures the left subtree (`ltree`) is valid and that the current token is
 *   a pipe.
 * - Creates a pipe node, assigns `ltree` as the left child, and constructs the 
 *   right child using `ft_ast_left`.
 * - Returns the pipe node or `NULL` if input validation fails.
 * 
 * @param t_ast *ltree				The left subtree of the pipe node.
 * @param t_minishell *minishell	The shell's state structure containing the
 * 									token list.
 * 
 * @return t_ast*					A pointer to the pipe node in the AST.
 * 
 * The function "ft_ast_left" constructs the left side of the AST by iterating 
 * through tokens of specific types (`TOKEN_COMMAND` or arguments).
 * 
 * - Starts with a command token and continues adding argument nodes to the 
 *   left.
 * - Frees tokens as they are consumed.
 * - Returns the root of the constructed left subtree or `NULL` if the input 
 *   is invalid.
 * 
 * @param t_minishell *minishell	The shell's state structure containing the
 * 									token list.
 * 
 * @return t_ast*					A pointer to the root of the constructed
 * 									left subtree.
 * 
 * The function "ft_ast_node" creates a new node for the Abstract Syntax Tree 
 * (AST).
 * 
 * - Allocates memory for a new `t_ast` node.
 * - Initializes the node with the given type and value, setting left and right 
 *   children to `NULL`.
 * - Returns the newly created node or `NULL` if memory allocation fails.
 * 
 * @param t_tok_typ_enum type	The token type to assign to the AST node.
 * @param char *value			The value associated with the node.
 * 
 * @return t_ast*				A pointer to the newly created AST node.
 * 
 */

t_ast	*ft_ast_node(t_tok_typ_enum type, char *value)
{
	t_ast	*tree;

	tree = malloc(sizeof(t_ast));
	if (!tree)
		return (NULL);
	tree->value = ft_strdup(value);
	tree->type = type;
	tree->right = NULL;
	tree->left = NULL;
	return (tree);
}

t_ast	*ft_ast_left(t_minishell *minishell)
{
	t_token	*temp;
	t_ast	*tree;
	t_ast	*temp_tree;

	temp = minishell->tokens;
	if (temp->token_type != 5 && temp->token_type != 7)
		return (ft_printf("Not valid input\n"), NULL);
	tree = ft_ast_node(minishell->tokens->token_type, \
	minishell->tokens->token_value);
	temp_tree = tree;
	minishell->tokens = minishell->tokens->next;
	ft_free_tokens(temp);
	while (minishell->tokens && (minishell->tokens->token_type == 6 \
	|| minishell->tokens->token_type == 7))
	{
		tree->left = ft_ast_node(minishell->tokens->token_type, \
		minishell->tokens->token_value);
		tree = tree->left;
		temp = minishell->tokens;
		minishell->tokens = minishell->tokens->next;
		ft_free_tokens(temp);
	}
	tree = temp_tree;
	return (tree);
}

t_ast	*ft_ast_pipe(t_ast *ltree, t_minishell *minishell)
{
	t_ast	*pipe_node;
	t_ast	*rtree;
	t_token	*temp;

	if (!ltree && minishell->tokens->token_type != 8)
	{
		ft_printf("Not valid input\n");
		return (NULL);
	}
	temp = minishell->tokens;
	pipe_node = ft_ast_node(minishell->tokens->token_type, \
	minishell->tokens->token_value);
	minishell->tokens = minishell->tokens->next;
	ft_free_tokens(temp);
	if (!minishell->tokens || minishell->tokens->token_type != 5)
	{
		ft_printf("Not valid input 2\n");
		return (NULL);
	}
	rtree = ft_ast_left(minishell);
	pipe_node->right = rtree;
	pipe_node->left = ltree;
	return (pipe_node);
}

t_ast	*ft_ast_redir_in(t_ast *ltree, t_minishell *minishell)
{
	t_ast	*redir_in_node;
	t_ast	*rtree;
	t_token	*temp;

	if (minishell->tokens->token_type != 1)
	{
		ft_printf("Not valid input\n");
		return (NULL);
	}
	temp = minishell->tokens;
	redir_in_node = ft_ast_node(minishell->tokens->token_type, \
	minishell->tokens->token_value);
	minishell->tokens = minishell->tokens->next;
	ft_free_tokens(temp);
	if (!minishell->tokens || minishell->tokens->token_type != 7)
	{
		ft_printf("Not valid input 2\n");
		return (NULL);
	}
	rtree = ft_ast_left(minishell);
	redir_in_node->left = ltree;
	redir_in_node->right = rtree;
	return (redir_in_node);
}
