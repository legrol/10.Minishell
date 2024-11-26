/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:50:37 by pabromer          #+#    #+#             */
/*   Updated: 2024/11/25 10:43:40 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * 
 * t_ast *ft_ast_node(t_tok_typ_enum type, char *value) create a new ast node.
 * 
 * t_ast	*ft_ast_left(t_minishell *minishell) if ast is a command put in 
 * left the next tokens while them are args or options
 * 
 * t_ast *ft_ast_pipe(t_ast *ltree, t_minishell *minishell) in the current ast 
 * create a pipe node at left alloc the previous ast and at right create a new 
 * ft_ast_left.
 * 
 * t_ast *ft_ast(t_minishell *minishell) move through the tokens and call the 
 * diferents mode creations
 * 
 */

/**
 * The function "ft_ast" constructs the full Abstract Syntax Tree (AST) by 
 * iterating through tokens and delegating to specific builders for commands, 
 * pipes, and redirections.
 * 
 * - Iterates through the token list and identifies token types.
 * - Constructs the AST incrementally by combining nodes for commands, pipes, 
 *   and redirections.
 * - Skips invalid tokens and ensures proper cleanup.
 * 
 * @param t_minishell *minishell	The shell's state structure containing the
 * 									token list.
 * 
 * @return t_ast*					A pointer to the root of the constructed 
 * 									AST.
 * 
 * The function "ft_ast_redir_heredoc" creates a node for heredoc input 
 * redirection (`<<`) in the Abstract Syntax Tree (AST).
 * 
 * - Validates the current token to ensure it corresponds to a heredoc 
 *   redirection operation.
 * - Creates a new AST node for the heredoc redirection and assigns the left 
 *   subtree (`ltree`).
 * - Parses the right subtree using `ft_ast_left` to handle the heredoc 
 *   terminator or command after the redirection.
 * - Frees the tokens as they are consumed and ensures proper error handling.
 * 
 * @param t_ast *ltree				The left subtree of the redirection node.
 * @param t_minishell *minishell	The shell's state structure containing the 
 * 									token list.
 * 
 * @return t_ast*					A pointer to the heredoc redirection node
 * 									in the AST, or `NULL` if input validation 
 * 									fails.
 * 
 * The function "ft_ast_redir_append" creates a node for append output 
 * redirection (`>>`) in the Abstract Syntax Tree (AST).
 * 
 * - Validates the current token to ensure it corresponds to an append 
 *   redirection operation.
 * - Creates a new AST node for the append redirection and assigns the left 
 *   subtree (`ltree`).
 * - Parses the right subtree using `ft_ast_left` to handle the target file 
 *   or command after the redirection.
 * - Frees the tokens as they are consumed and ensures proper error handling.
 * 
 * @param t_ast *ltree				The left subtree of the redirection node.
 * @param t_minishell *minishell	The shell's state structure containing the 
 * 									token list.
 * 
 * @return t_ast*					A pointer to the append redirection node in
 * 									the AST, or `NULL` if input validation 
 * 									fails.
 * 
 * The function "ft_ast_redir_out" creates a node for output redirection (`>`) 
 * in the Abstract Syntax Tree (AST).
 * 
 * - Validates the current token to ensure it corresponds to an output 
 *   redirection operation.
 * - Creates a new AST node for the redirection and assigns the left subtree 
 *   (`ltree`).
 * - Parses the right subtree using `ft_ast_left` to handle the target file 
 *   or command after the redirection.
 * - Frees the tokens as they are consumed and ensures proper error handling.
 * 
 * @param t_ast *ltree				The left subtree of the redirection node.
 * @param t_minishell *minishell	The shell's state structure containing the
 * 									token list.
 * 
 * @return t_ast*					A pointer to the output redirection node in
 * 									the AST, or `NULL` if input validation
 * 									fails.
 * 
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

static t_ast	*ft_ast_node(t_tok_typ_enum type, char *value)
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

static t_ast	*ft_ast_left(t_minishell *minishell)
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

static t_ast	*ft_ast_pipe(t_ast *ltree, t_minishell *minishell)
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

static t_ast	*ft_ast_redir_in(t_ast *ltree, t_minishell *minishell)
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

static t_ast	*ft_ast_redir_out(t_ast *ltree, t_minishell *minishell)
{
	t_ast	*redir_out_node;
	t_ast	*rtree;
	t_token	*temp;

	if (minishell->tokens->token_type != 2)
	{
		ft_printf("Not valid input\n");
		return (NULL);
	}
	temp = minishell->tokens;
	redir_out_node = ft_ast_node(minishell->tokens->token_type, \
	minishell->tokens->token_value);
	minishell->tokens = minishell->tokens->next;
	ft_free_tokens(temp);
	if (!minishell->tokens || minishell->tokens->token_type != 7)
	{
		ft_printf("Not valid input 2\n");
		return (NULL);
	}
	rtree = ft_ast_left(minishell);
	redir_out_node->left = ltree;
	redir_out_node->right = rtree;
	return (redir_out_node);
}

static t_ast	*ft_ast_redir_append(t_ast *ltree, t_minishell *minishell)
{
	t_ast	*redir_append_node;
	t_ast	*rtree;
	t_token	*temp;

	if (minishell->tokens->token_type != 3)
	{
		ft_printf("Not valid input\n");
		return (NULL);
	}
	temp = minishell->tokens;
	redir_append_node = ft_ast_node(minishell->tokens->token_type, \
	minishell->tokens->token_value);
	minishell->tokens = minishell->tokens->next;
	ft_free_tokens(temp);
	if (!minishell->tokens || minishell->tokens->token_type != 7)
	{
		ft_printf("Not valid input 2\n");
		return (NULL);
	}
	rtree = ft_ast_left(minishell);
	redir_append_node->left = ltree;
	redir_append_node->right = rtree;
	return (redir_append_node);
}

static t_ast	*ft_ast_redir_heredoc(t_ast *ltree, t_minishell *minishell)
{
	t_ast	*redir_heredoc_node;
	t_ast	*rtree;
	t_token	*temp;

	if (minishell->tokens->token_type != 4)
	{
		ft_printf("Not valid input\n");
		return (NULL);
	}
	temp = minishell->tokens;
	redir_heredoc_node = ft_ast_node(minishell->tokens->token_type, \
	minishell->tokens->token_value);
	minishell->tokens = minishell->tokens->next;
	ft_free_tokens(temp);
	if (!minishell->tokens || minishell->tokens->token_type != 7)
	{
		ft_printf("Not valid input 2\n");
		return (NULL);
	}
	rtree = ft_ast_left(minishell);
	redir_heredoc_node->left = ltree;
	redir_heredoc_node->right = rtree;
	return (redir_heredoc_node);
}

t_ast *ft_ast(t_minishell *minishell)
{
	t_ast	*tree;

	if (!minishell->tokens)
	{
		ft_printf("Not valid input\n");
		return (NULL);
	}
	while (minishell->tokens)
	{
		if (minishell->tokens->token_type == 5)
			tree = ft_ast_left(minishell);
		else if (minishell->tokens->token_type == 8)
			tree = ft_ast_pipe(tree, minishell);
		else if (minishell->tokens->token_type == 1)
			tree = ft_ast_redir_in(tree, minishell);
		else if (minishell->tokens->token_type == 2)
			tree = ft_ast_redir_out(tree, minishell);
		else if (minishell->tokens->token_type == 3)
			tree = ft_ast_redir_append(tree, minishell);
		else if (minishell->tokens->token_type == 4)
			tree = ft_ast_redir_heredoc(tree, minishell);
		else
			minishell->tokens = minishell->tokens->next;
	}
	return (tree);
}

