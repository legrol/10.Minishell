/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:53:36 by pabromer          #+#    #+#             */
/*   Updated: 2024/11/05 11:48:42 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * The function "ft_change_env" modifies or adds an environment variable 
 * in the shell's environment variables linked list (`t_envp`).
 * 
 * - If the key (`str1`) already exists in the list, updates its value 
 *   (`str2`):
 *   - Frees the existing value if it is not `NULL`.
 *   - Duplicates the new value (`str2`) if provided; otherwise, sets it to 
 *     `NULL`.
 * - If the key does not exist in the list, creates a new node with the given 
 *   key and value and prepends it to the linked list.
 * - Ensures that the `list_envp` pointer in the `t_minishell` structure 
 *   points to the head of the updated list.
 * 
 * @param t_minishell *minishell	A pointer to the shell's state structure, 
 *									which contains the environment variables
 *									linked list.
 * @param const char *str1			The key of the environment variable to 
 * 									modify or add.
 * @param const char *str2			The new value for the environment variable. 
 * 									If `NULL`, the value is set to `NULL`.
 * 
 * @return void						This function does not return a value.
 * 
 * The function "new_node_envp" creates a new node for the environment 
 * variables linked list (`t_envp`).
 * 
 * - Allocates memory for a new node of type `t_envp`.
 * - Copies the given `key` and `value` into the new node. If `value` is
 *   `NULL`, 
 *   the `value` field in the node is set to `NULL`.
 * - Sets the `next` pointer of the new node to `NULL`.
 * - Returns the newly created node, or `NULL` if memory allocation fails.
 * 
 * @param char *key		The key of the environment variable to store in the
 * 						node.
 * @param char *value	The value of the environment variable to store in the
 * 						node. If `NULL`, the value field is set to `NULL`.
 * 
 * @return t_envp*		A pointer to the newly created environment variable 
 * 						node, or `NULL` if memory allocation fails. 
 * 
 */

static t_envp	*new_node_envp(char *key, char *value)
{
	t_envp	*new_node;

	new_node = (t_envp *)malloc(sizeof(t_envp));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (!value)
		new_node->value = NULL;
	else
		new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}

void	ft_change_env(t_minishell *minishell, const char *str1, \
		const char *str2)
{
	t_envp	*temp;
	t_envp	*new_node;

	if (!str1)
		return ;
	temp = minishell->list_envp;
	while (minishell->list_envp)
	{
		if (ft_strcmp(minishell->list_envp->key, (char *)str1) == 0)
		{
			if (minishell->list_envp->value)
				free(minishell->list_envp->value);
			if (str2)
				minishell->list_envp->value = ft_strdup(str2);
			else
				minishell->list_envp->value = NULL;
			minishell->list_envp = temp;
			return ;
		}
		minishell->list_envp = minishell->list_envp->next;
	}
	new_node = new_node_envp((char *)str1, (char *)str2);
	new_node->next = temp;
	minishell->list_envp = new_node;
}
