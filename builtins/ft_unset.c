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
 * The function "ft_remove_key" removes an environment variable from the 
 * linked list of environment variables in the `t_minishell` structure.
 * It searches the list for a node matching the key provided in the `ast` node.
 * If a match is found, it removes the node, frees its memory, and updates 
 * the linked list accordingly.
 * 
 * @param t_minishell *minishell	A pointer to the `t_minishell` structure
 *									that holds the linked list of environment 
 *									variables (`list_envp`).
 * 
 * @param t_ast *ast				A pointer to the `t_ast` structure 
 * 									containing the key (in `ast->value`) to be
 * 									removed from the environment variables 
 * 									list.
 * 
 * The function "ft_unset" removes one or more environment variables from the 
 * shell's environment. It traverses the `ast` linked list, which contains the
 * keys of the environment variables to be removed, and calls `ft_remove_key` 
 * for each key.
 * 
 * @param t_minishell *minishell	A pointer to the `t_minishell` structure
 *									that holds the linked list of environment 
 *									variables (`list_envp`).
 * 
 * @param t_ast *ast				A pointer to the `t_ast` structure that 
 *									represents a list of keys to be removed 
 *									from the environment variables.
 * 
 */

static void	ft_remove_key(t_minishell *minishell, t_ast *ast)
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
			break ;
		}
		prev = current;
		current = current->next;
	}
	minishell->list_envp = head;
}

void	ft_unset(t_minishell *minishell, t_ast *ast)
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
