/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:45:06 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/10/29 17:11:24 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "free_tokens" releases all memory allocated for a linked list
 * of tokens. It iterates through each node in the list, freeing the memory
 * allocated for each token's value and then the node itself.
 * 
 * @param t_token *token		A pointer to the head of the linked list of 
 * 								tokens (`t_token`). This list will be fully 
 * 								deallocated by the function.
 * 
 */

void	ft_free_tokens(t_token *token)
{
	t_token	*current;
	t_token	*next;

	current = token;
	while (current != NULL)
	{
		next = current->next;
		free(current->token_value);
		free(current);
		current = next;
	}
}
