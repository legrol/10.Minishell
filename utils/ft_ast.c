/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:50:37 by pabromer          #+#    #+#             */
/*   Updated: 2024/11/08 15:28:25 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_ast *ft_ast_node(t_tok_typ_enum type, char *value, t_ast *left)
{
	t_ast	*tree;

	tree = malloc(sizeof(t_ast));
	if (!tree)
		return (NULL);
	tree->value = ft_strdup(value);
	tree->type = type;
	tree->right = NULL;
	tree->left = left;
	return (tree);
}

t_ast	*ft_ast_left(t_minishell *minishell)
{
	t_token *temp;
	t_ast	*tree;
	t_ast	*temp_tree;

	temp = minishell->tokens;
	if(temp->token_type != 5)
	{
		printf("Not valid input\n");
		return NULL;
	}
	tree = ft_ast_node(minishell->tokens->token_type, minishell->tokens->token_value, NULL);
	temp_tree = tree;
	minishell->tokens = minishell->tokens->next;
	while (minishell->tokens && (minishell->tokens->token_type == 6 || minishell->tokens->token_type == 7))
	{
		tree->left = ft_ast_node(minishell->tokens->token_type, minishell->tokens->token_value, NULL);
		tree = tree->left;
		minishell->tokens = minishell->tokens->next;
	}
	tree = temp_tree;
	return (tree);
}

t_ast *ft_ast_pipe(t_ast *ltree, t_minishell *minishell)
{
	t_ast 	*pipe_node;
	t_ast	*right_cmd;

	if(minishell->tokens->token_type != 8)
	{
		printf("Not valid input\n");
		return NULL;
	}
	pipe_node = ft_ast_node(minishell->tokens->token_type, minishell->tokens->token_value, NULL);
	minishell->tokens = minishell->tokens->next;
	if(!minishell->tokens || minishell->tokens->token_type != 5)
	{
		printf("Not valid input 2\n");
		return NULL;
	}
	right_cmd = ft_ast_left(minishell);
	pipe_node->left = ltree;
	pipe_node->right = right_cmd;
	return pipe_node;

}

t_ast *ft_ast(t_minishell *minishell)
{
	t_ast	*tree;
	
	if(!minishell->tokens)
	{
		printf("Not valid input\n");
		return NULL;
	}
	while (minishell->tokens)
	{
		if(minishell->tokens->token_type == 5)
			tree =ft_ast_left(minishell);
		else if (minishell->tokens->token_type == 8)
			tree =ft_ast_pipe(tree, minishell);
		else
			minishell->tokens = minishell->tokens->next;
	}
	return (tree);
}

