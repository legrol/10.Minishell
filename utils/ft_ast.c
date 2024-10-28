/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:50:37 by pabromer          #+#    #+#             */
/*   Updated: 2024/10/28 16:55:12 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_ast(t_minishell *minishell)
{
	t_token *temp;
	t_ast	*tree;
	//t_ast	*temp_tree;

	temp = minishell->tokens;
	if(temp->token_type == 0 || temp->token_type == 6 || temp->token_type == 7 || temp->token_type == 8)
	{
		printf("Not valid input\n");
		return ;
	}
	tree = malloc(sizeof(t_ast));
	if (!tree)
		return ;
	tree->value = ft_strdup(minishell->tokens->token_value);
	tree->type = minishell->tokens->token_type;
	tree->right = NULL;
	tree->left =NULL;
	minishell->tokens = temp;
}