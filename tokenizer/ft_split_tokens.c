/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-31 11:01:14 by rdel-olm          #+#    #+#             */
/*   Updated: 2024-10-31 11:01:14 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_split_and_update_tokens" combines the splitting and type 
 * updating for a token.
 * 
 * @param t_token *token		A pointer to the token to be processed.
 * 
 * The function "ft_split_tokens" splits a token's value by a delimiter and 
 * creates new linked tokens for each part.
 * 
 * @param t_token *token		A pointer to the token to be split.
 * @return t_token* 			A pointer to the last token created in the 
 * 								chain.
 *
 * The function "ft_update_tokens" updates the types of all tokens in a linked
 * list starting from the given token.
 * 
 * @param t_token *token		A pointer to the starting token to be updated.
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

t_token	*ft_split_tokens(t_token *token)
{
	int			i;
	t_token		*current;
	char		**sub_tokens;

	if (!ft_strchr(token->token_value, '|'))
		return (token);

	sub_tokens = ft_split(token->token_value, '|');
	if (!sub_tokens)
		return (token);
	current = token;
	i = 0;

	while (sub_tokens[i])
	{
		free(current->token_value);
		current->token_value = strdup(sub_tokens[i]);
		if (!current->token_value)
		{
			ft_free_split(sub_tokens);
			return (NULL);
		}
		if (sub_tokens[i + 1])
		{
			current->next = malloc(sizeof(t_token));
			if (!current->next)
			{
				ft_free_split(sub_tokens);
				return (NULL);
			}
			current->next->prev = current;
			current = current->next;
			current->next = NULL;
		}
		i++;
	}
	ft_free_split(sub_tokens);
	return (current);
}

void	ft_split_and_update_tokens(t_token *token)
{
	t_token	*last_token;

	last_token = ft_split_tokens(token);
	ft_update_tokens(token);
}
