/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:50:37 by pabromer          #+#    #+#             */
/*   Updated: 2024/11/07 10:13:00 by pabromer         ###   ########.fr       */
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
	t_token *temp;
	t_ast	*tree;

	ft_printf("Dentro PIPE\n");
	temp = minishell->tokens;
	if(temp->token_type != 8)
	{
		printf("Not valid input\n");
		return NULL;
	}

}

t_ast *ft_ast(t_minishell *minishell)
{
	t_token *temp;
	t_ast	*tree;
	t_ast	*temp_tree;
	t_ast	*ltree;
	//t_ast	*ltemp;

	temp = minishell->tokens;
	if(temp->token_type != 5)
	{
		printf("Not valid input\n");
		return NULL;
	}
	tree = ft_ast_left(minishell);
	if (minishell->tokens)
	{
		ft_printf("CONTINUANDO\n");
		ltree = tree;
		tree = tree->right;
	}
	else 
	{
		ft_printf("SALIENDO\n");
		minishell->tokens = temp;
		return (tree);
	}
	
	minishell->tokens = temp;
	tree = temp_tree;
	return (tree);
}

