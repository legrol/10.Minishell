/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_envp_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:41:34 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/10/29 20:08:49 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * 
 * The funbction "ft_free_envp_list" releases all memory allocated for the linked
 * list of environment variables. It iterates through each node in the list,
 * freeing the memory for each key-value pair and then the node itself.
 * 
 * @param t_envp *envp_list	A pointer to the head of the linked list of 
 * 							environment variables (`t_envp`). This list will
 * 							be fully deallocated by the function. 
 * 
 */

void	ft_free_envp_list(t_envp *envp_list)
{
	t_envp	*temp;

	while (envp_list)
	{
		temp = envp_list;
		envp_list = envp_list->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}
