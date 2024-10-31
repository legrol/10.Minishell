/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:38:17 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/10/31 16:38:35 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * 
 * 
 * 
 * 
 */

static void ft_remove_key(t_minishell *minishell, t_ast *ast)
{
	t_envp	*current;
	t_envp	*prev;
	t_envp	*head;

	prev = NULL;
	current = minishell->list_envp;
	head = minishell->list_envp;
	while (current)
	{
		if (ft_strcmp(current->key, ast->value) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				head = current->next;
			free(current->key);
			free(current->value);
			free(current);
			break;
		}
		prev = current;
		current = current->next;
	}
	minishell->list_envp = head;
}

void ft_unset(t_minishell *minishell, t_ast *ast)
{
	t_ast	*temp;

	temp = ast;
	while (ast)
	{
		ft_remove_key(minishell, ast);
		ast = ast->left;
	}
	ast = temp;
}
