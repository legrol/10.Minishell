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
 * The function "ft_unset" removes one or more environment variables from 
 * the shell's environment. It iterates through a linked list of keys 
 * represented by the `ast` structure and calls `ft_remove_key` for each key 
 * to remove it from the environment variables list.
 * 
 * The function traverses the `ast` structure recursively, ensuring that each
 * specified key is processed and removed from the `list_envp` in the 
 * `t_minishell` structure. It manages memory carefully, ensuring no leaks
 * occur during the removal process.
 * 
 * @param t_minishell *minishell	A pointer to the `t_minishell` structure
 *									that holds the shell's environment state,
 *									including the linked list of environment 
 *									variables (`list_envp`).
 * 
 * @param t_ast *ast				A pointer to the `t_ast` structure that 
 *									represents a list of keys to be removed 
 *									from the environment variables. Each node 
 *									in the `ast` contains a key to be 
 *									processed.
 *
 *
 * The function "ft_remove_key" removes an environment variable from the
 * linked list of environment variables stored in the `t_minishell` structure.
 * It searches for a node in the list that matches the key specified in the 
 * `ast->value` field. If a match is found, the node is removed, its memory 
 * is freed, and the linked list is updated to maintain consistency.
 * 
 * The function ensures proper memory management by freeing the memory
 * allocated for both the `key` and `value` fields of the node, as well as
 * the node itself. If no matching key is found, the linked list remains
 * unchanged.
 * 
 * @param t_minishell *minishell	A pointer to the `t_minishell` structure,
 *									which contains the linked list of 
 *									environment variables (`list_envp`).
 * 
 * @param t_ast *ast				A pointer to the `t_ast` structure 
 *									containing the key (in `ast->value`) 
 *									of the environment variable to be removed. 
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
