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
	{
		printf("Not valid input\n");
		return (NULL);
	}
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
		printf("Not valid input\n");
		return (NULL);
	}
	temp = minishell->tokens;
	pipe_node = ft_ast_node(minishell->tokens->token_type, \
	minishell->tokens->token_value);
	minishell->tokens = minishell->tokens->next;
	ft_free_tokens(temp);
	if (!minishell->tokens || minishell->tokens->token_type != 5)
	{
		printf("Not valid input 2\n");
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
		printf("Not valid input\n");
		return (NULL);
	}
	temp = minishell->tokens;
	redir_in_node = ft_ast_node(minishell->tokens->token_type, \
	minishell->tokens->token_value);
	minishell->tokens = minishell->tokens->next;
	ft_free_tokens(temp);
	if (!minishell->tokens || minishell->tokens->token_type != 7)
	{
		printf("Not valid input 2\n");
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
		printf("Not valid input\n");
		return (NULL);
	}
	temp = minishell->tokens;
	redir_out_node = ft_ast_node(minishell->tokens->token_type, \
	minishell->tokens->token_value);
	minishell->tokens = minishell->tokens->next;
	ft_free_tokens(temp);
	if (!minishell->tokens || minishell->tokens->token_type != 7)
	{
		printf("Not valid input 2\n");
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
		printf("Not valid input\n");
		return (NULL);
	}
	temp = minishell->tokens;
	redir_append_node = ft_ast_node(minishell->tokens->token_type, \
	minishell->tokens->token_value);
	minishell->tokens = minishell->tokens->next;
	ft_free_tokens(temp);
	if (!minishell->tokens || minishell->tokens->token_type != 7)
	{
		printf("Not valid input 2\n");
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
		printf("Not valid input\n");
		return (NULL);
	}
	temp = minishell->tokens;
	redir_heredoc_node = ft_ast_node(minishell->tokens->token_type, \
	minishell->tokens->token_value);
	minishell->tokens = minishell->tokens->next;
	ft_free_tokens(temp);
	if (!minishell->tokens || minishell->tokens->token_type != 7)
	{
		printf("Not valid input 2\n");
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
		printf("Not valid input\n");
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

