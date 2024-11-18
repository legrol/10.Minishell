/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tokens2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:01:14 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/17 17:20:48 by rdel-olm         ###   ########.fr       */
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

// static void	ft_update_tokens(t_token *token)
// {
// 	while (token)
// 	{
// 		ft_update_type_tokens(token);
// 		token = token->next;
// 	}
// }

static t_token	*ft_create_new_token(t_token *current, char *value)
{
	t_token *new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);	
	new_node->token_value = strdup(value);
	if (!new_node->token_value)
	{
		free(new_node);
		return (NULL);
	}
	new_node->prev = current;
	new_node->next = NULL;
	if (current)
		current->next = new_node;
	return (new_node);
}

static t_token	*ft_split_tokens(t_token *token)
{
	int		i;
	char	*token_value;
	t_token	*current;

	token_value = token->token_value;
	current = token;
	if (strchr(token_value, '|'))
	{
		char **sub_tokens = ft_split(token_value, '|');
		if (!sub_tokens)
			return (token);
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
		ft_free_split(sub_tokens);
	}
	current = token;
	while (current)
	{
		if (strchr(token_value, '-'))
		{
			ft_printf(ORANGE"token_value: %s\n"RESET, token_value); //ELIMINAR	
		}
		
		char *delimiter_position = strchr(current->token_value, '-');
		ft_printf(RED"delimiter_position: %s\n"RESET, delimiter_position); //ELIMINAR
		
		// verifica que no es NULL 									delimiter_position
		// verifica que el "-" no esta al inicio del token 			delimiter_position != current->token_value
		// verifica que el "-" no esta al final del token 			*(delimiter_position + 1) != '\0'
		if (delimiter_position && delimiter_position != current->token_value && *(delimiter_position + 1) != '\0')
		{
			int prefix_length = delimiter_position - current->token_value;
			ft_printf("prefix_length: %i\n", prefix_length); //ELIMINAR
			if (prefix_length > 0)
			{
				char *first_part = strndup(current->token_value, prefix_length);
				ft_printf("first_part: %s\n", first_part); //ELIMINAR
				if (!first_part)
					return (NULL);
				free(current->token_value);
				current->token_value = first_part;
				ft_printf("current->token_value: %s\n", current->token_value); //ELIMINAR
				current = ft_create_new_token(current, delimiter_position);
				if (!current)
					return (NULL);				
			}
		}
		current = current->next;
	}	
	return token;
}
 
void	ft_split_and_update_tokens(t_token *token)
{
	t_token	*last_token;

	last_token = ft_split_tokens(token);
	//ft_split_tokens(token);
	ft_update_tokens(last_token);
}
