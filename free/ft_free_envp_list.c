/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_envp_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-28 12:41:34 by rdel-olm          #+#    #+#             */
/*   Updated: 2024-10-28 12:41:34 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * 
 * The funbction "free_envp_list" releases all memory allocated for the linked
 * list of environment variables. It iterates through each node in the list,
 * freeing the memory for each key-value pair and then the node itself.
 * 
 * @param t_envp *head		A pointer to the head of the linked list of 
 * 							environment variables (`t_envp`). This list will
 * 							be fully deallocated by the function. 
 * 
 */

void	free_envp_list(t_envp *head)
{
	t_envp	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}
