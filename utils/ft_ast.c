/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:50:37 by pabromer          #+#    #+#             */
/*   Updated: 2024/10/30 12:28:30 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_ast *ft_ast_node(t_tok_typ_enum type, char *value)
{
	t_ast	*tree;

	tree = malloc(sizeof(t_ast));
	if (!tree)
		return (NULL);
	tree->value = ft_strdup(value);
	tree->type = type;
	tree->right = NULL;
	tree->left =NULL;
	return (tree);
}

t_ast	*ft_ast(t_minishell *minishell)
{
	t_token *temp;
	t_ast	*tree;
	t_ast	*temp_tree;
	//t_ast	*temp_tree2;

	temp = minishell->tokens;
	if(temp->token_type != 5)
	{
		printf("Not valid input\n");
		return NULL;
	}
	tree = ft_ast_node(minishell->tokens->token_type, minishell->tokens->token_value);
	temp_tree = tree;
	//printf("Type %i  Value %s\n", tree->type, tree->value);
	minishell->tokens = minishell->tokens->next;
	while (minishell->tokens && (minishell->tokens->token_type == 6 || minishell->tokens->token_type == 7))
	{
		tree->left = ft_ast_node(minishell->tokens->token_type, minishell->tokens->token_value);
		//printf("Type %i  Value %s\n", tree->type, tree->value);
		tree = tree->left;
		minishell->tokens = minishell->tokens->next;
	}
	tree = temp_tree;
	while (tree)
	{
		//printf("Type %i  Value %s\n", tree->type, tree->value);
		tree = tree->left;
	}
	tree = temp_tree;
	/*if (minishell->tokens && minishell-> tokens->token_type == 8)
	{
		tree->right = ft_ast_node(minishell->tokens->token_type, minishell->tokens->token_value);
		tree->right->left = temp_tree;
		minishell->tokens = minishell->tokens->next;
		tree->right->right = ft_ast(minishell);
	}*/
	return (tree);
}
