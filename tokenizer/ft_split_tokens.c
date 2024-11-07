/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:01:14 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/07 20:02:12 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_split_and_update_tokens" combines the process of splitting 
 * a token and updating the types of tokens in the linked list.
 * 
 * @param t_token *token		A pointer to the token to be processed. This 
 *								function updates the list by splitting the 
 *								token and adjusting their types.
 * 
 * The function "ft_split_tokens" splits the value of the given token by a 
 * delimiter (e.g., '|') and creates a linked list of new tokens for each 
 * part. It modifies the original token and adds new tokens as needed.
 * 
 * @param t_token *token		A pointer to the token to be split.
 * @return t_token*				A pointer to the last token created in the 
 *								list or NULL if memory allocation fails.
 *
 * The function "ft_create_new_token" creates a new token, sets its value, 
 * links it to the previous token, and returns the newly created token.
 * 
 * @param t_token *current		A pointer to the current token, which will be 
 *								linked to the new token.
 * @param char *value			A string containing the value for the new token.
 * @return t_token*				A pointer to the newly created token, or NULL 
 *								if memory allocation fails.
 * 
 * The function "ft_update_tokens" iterates through a linked list of tokens
 * and updates their types based on their values and positions.
 * 
 * @param t_token *token		A pointer to the starting token in the 
 *								linked list. Each token's type will be updated.
 * 
 */

static void	ft_update_tokens(t_token *token)
{
	while (token)
	{
		ft_update_type_tokens(token);
		token = token->next;
	}
}

static t_token	*ft_create_new_token(t_token *current, char *value)
{
	current->next = malloc(sizeof(t_token));
	if (!current->next)
		return (NULL);
	current->next->prev = current;
	current = current->next;
	current->token_value = strdup(value);
	current->next = NULL;
	return (current);
}

static t_token	*ft_split_tokens(t_token *token)
{
	int		i;
	char	**sub_tokens;
	t_token	*current;

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
		current->token_value = strdup(sub_tokens[i++]);
		if (!current->token_value)
			return (ft_free_split(sub_tokens), NULL);
		if (sub_tokens[i])
		{
			current = ft_create_new_token(current, sub_tokens[i]);
			if (!current)
				return (ft_free_split(sub_tokens), NULL);
		}
	}
	return (ft_free_split(sub_tokens), token);
}

void	ft_split_and_update_tokens(t_token *token)
{
	t_token	*last_token;

	last_token = ft_split_tokens(token);
	ft_update_tokens(last_token);
	//ft_update_tokens(token);
}
