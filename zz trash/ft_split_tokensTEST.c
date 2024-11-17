/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:01:14 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/12 19:21:29 by rdel-olm         ###   ########.fr       */
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
static t_token	*ft_create_new_token(t_token *current, const char *value)
{
	t_token *new_token = malloc(sizeof(t_token));
	if (!new_token)
		return NULL;

	new_token->token_value = strdup(value);
	if (!new_token->token_value)
	{
		free(new_token);
		return NULL;
	}
	new_token->prev = current;
	new_token->next = NULL;
	if (current)
		current->next = new_token;

	return new_token;
}

static t_token	*ft_split_tokens(t_token *token)
{
	int		i;
	char	**space_split;
	t_token	*current;

	// Primero, dividir el token por espacios para manejar `ls -l`
	space_split = ft_split(token->token_value, ' ');
	if (!space_split)
		return token;

	current = token;
	i = 0;

	// Iterar sobre tokens separados por espacio
	while (space_split[i])
	{
		// Reemplazar el valor del primer token
		if (i == 0)
		{
			free(current->token_value);
			current->token_value = strdup(space_split[i]);
			if (!current->token_value)
				return (ft_free_split(space_split), NULL);
		}
		else
		{
			// Crear un nuevo token para cada parte y enlazarlo
			current = ft_create_new_token(current, space_split[i]);
			if (!current)
				return (ft_free_split(space_split), NULL);
		}
		i++;
	}
	ft_free_split(space_split);

	// Segundo, revisar cada token y dividir por `|` si está presente
	current = token;
	while (current)
	{
		if (ft_strchr(current->token_value, '|'))
		{
			// Dividir el token actual por `|` y actualizar la lista
			char **pipe_split = ft_split(current->token_value, '|');
			if (!pipe_split)
				return token;

			free(current->token_value);
			current->token_value = strdup(pipe_split[0]);
			if (!current->token_value)
				return (ft_free_split(pipe_split), NULL);

			int j = 1;
			while (pipe_split[j])
			{
				// Crear y enlazar un nuevo token para `|`
				current = ft_create_new_token(current, "|");
				if (!current)
					return (ft_free_split(pipe_split), NULL);

				// Crear y enlazar el siguiente token
				current = ft_create_new_token(current, pipe_split[j++]);
				if (!current)
					return (ft_free_split(pipe_split), NULL);
			}
			ft_free_split(pipe_split);
		}
		current = current->next;
	}
	return token;
}

void	ft_split_and_update_tokens2(t_token *token)
{
	t_token	*last_token;

	last_token = ft_split_tokens(token);
	ft_update_tokens(last_token);
}
