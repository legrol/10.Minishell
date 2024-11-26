/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:01:14 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/25 17:05:17 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_update_tokens" iterates through a linked list of tokens 
 * and updates the type of each token using the `ft_update_type_tokens` 
 * function. This function ensures that each token's type is correctly set 
 * based on its value or context in the shell.
 * 
 * - The function traverses the linked list starting from the given `token`.
 * - For each token, it calls `ft_update_type_tokens`, which handles the logic 
 *   for determining and setting the token's type.
 * - Continues updating tokens until it reaches the end of the list 
 *   (`token == NULL`).
 * 
 * @param t_token *token	A pointer to the head of the token linked list.
 *							This list contains all tokens generated during 
 *							the tokenization phase of user input.
 * 
 * @return void				This function does not return a value. It updates 
 *							the type field of each token in the linked list in 
 *							place.
 * 
 */

void	ft_update_tokens(t_token *token)
{
	while (token)
	{
		ft_update_type_tokens(token);
		token = token->next;
	}
}
