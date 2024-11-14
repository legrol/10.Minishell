/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:01:14 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/14 22:35:52 by rdel-olm         ###   ########.fr       */
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
	current->next = new_node;
	return (new_node);
}

static t_token *ft_split_tokens(t_token *token)
{
	char **sub_tokens;
	t_token *current = token;
	t_token *last_node = NULL;
	int	i = 0;
	int j = 0; //ELIMINAR

	ft_printf(CYAN"Estoy en split_tokens\n"RESET);  //ELIMINAR
	ft_printf(GREEN"param_token_value = %s\n"RESET, token->token_value); //ELIMINAR
	ft_printf(GREEN"current_token = %s\n"RESET, current->token_value);	//ELIMINAR

	if (ft_strchr(token->token_value, '-'))
	{
		sub_tokens = ft_split_minus(token->token_value, '-');

		while (sub_tokens[i] != NULL) //ELIMINAR
		{ //ELIMINAR
			ft_printf("sub_token = %s i = %i\n", sub_tokens[i], i); //ELIMINAR
			i++; //ELIMINAR
		} //ELIMINAR

		i = 0;		
		while (sub_tokens[i])
		{
			ft_printf("\nsub_token = %s i = %i\n", sub_tokens[i], i); //ELIMINAR
			if (i == 0)
			{
				free(current->token_value);
				current->token_value = strdup(sub_tokens[i]);
				if (!current->token_value)
					return (ft_free_split(sub_tokens), NULL);
				ft_printf("index = %i current_token_value = %s\n", i, current->token_value); //ELIMINAR
			}
			else
			{
				ft_printf("Entro en else secundario\n"); //ELIMINAR
				// last_node = ft_create_new_token(last_node, sub_tokens[i]); //ELIMINAR
				last_node = ft_create_new_token(current, sub_tokens[i]);
				if (!last_node)
					return (ft_free_split(sub_tokens), NULL);
				// if (!current) //ELIMINAR
				// 	return (ft_free_split(sub_tokens), NULL); //ELIMINAR
				ft_printf("new_node_token_value = %s\n", current->token_value); //ELIMINAR
				ft_printf("new_node_next_token_value = %s\n", current->next->token_value); //ELIMINAR
			}
			i++;
		}

		while (current != NULL) //ELIMINAR
		{ //ELIMINAR
			ft_printf("Token_current %d: %s\n", j, current->token_value); //ELIMINAR
        	current = current->next; //ELIMINAR
        	j++; //ELIMINAR
		} //ELIMINAR

		ft_free_split(sub_tokens);
	}
	else
	{
		ft_printf("Entro en else principal si no hay un -\n"); //ELIMINAR
		current->token_value = strdup(token->token_value);
		if (!current->token_value)
			return NULL;
		ft_printf("single_token_value = %s\n", current->token_value); //ELIMINAR
	}

	return last_node;
}

void ft_split_and_update_tokens(t_token *token)
{
	t_token *current = token;
	t_token *last_token = NULL;
	int j = 0;

	while (current)
	{
		last_token = ft_split_tokens(current);
		ft_printf("Verificando el last_token en principal\n"); //ELIMINAR
		while (last_token != NULL) //ELIMINAR
		{ //ELIMINAR
			ft_printf("Token_last_token %d: %s\n", j, last_token->token_value); //ELIMINAR
        	last_token = last_token->next; //ELIMINAR
        	j++; //ELIMINAR
		} //ELIMINAR

		// if (!last_token)
		// {
		// 	ft_printf("Saliendo de principal\n");
		// 	return;
		// }
		
		ft_printf("Último token después de split_tokens: %s\n\n", last_token->token_value); //ELIMINAR
		if (last_token->next == NULL)
			current = current->next;
		else
			current = last_token->next;
	}
	t_token *temp = token;
	ft_printf("\nLista de tokens final:\n"); //ELIMINAR
	while (temp) //ELIMINAR
	{ //ELIMINAR
		ft_printf("Token en lista: %s\n", temp->token_value); //ELIMINAR
		temp = temp->next; //ELIMINAR
	} //ELIMINAR
	ft_update_tokens(token);
}
