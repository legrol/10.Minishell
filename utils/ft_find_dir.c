/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:53:36 by pabromer          #+#    #+#             */
/*   Updated: 2024/11/04 12:15:51 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
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
 * 						node. 
 * 						If `NULL`, the value field is set to `NULL`.
 * 
 * @return t_envp*		A pointer to the newly created environment variable 
 * 						node, or `NULL` if memory allocation fails. 
 * 
 */

char	*ft_find_dir(t_minishell *minishell, const char *str)
{
	char	*result;
	t_envp	*temp;

	if (!str)
		return (NULL);
	temp = minishell->list_envp;
	while (minishell->list_envp)
	{
		if (ft_strcmp(minishell->list_envp->key, (char *)str) == 0)
		{
			result = minishell->list_envp->value;
			minishell->list_envp = temp;
			return (result);
		}
		minishell->list_envp = minishell->list_envp->next;
	}
	minishell->list_envp = temp;
	return (NULL);
}
