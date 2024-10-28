/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-28 12:45:06 by rdel-olm          #+#    #+#             */
/*   Updated: 2024-10-28 12:45:06 by rdel-olm         ###   ########.fr       */
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

void	free_tokens(t_token *token)
{
	t_token	*temp;

	while (token)
	{
		temp = token;
		token = token->next;
		free(temp->token_value);
		free(temp);
	}
}