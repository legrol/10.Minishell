/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_token_minus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:35:24 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/14 22:36:15 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "" xxx
 * 
 * @param			xxx
 * 
 * @return			xxx 
 * 
 *  ELIMINAR ?????
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

static ft_split_tokens(t_token *token)
{
	int		i;
	char	**sub_tokens;
	t_token	*current;

	if (!ft_strchr(token->token_value, '-'))
		return (token);
	sub_tokens = ft_split_minus(token->token_value, '-');
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

void ft_split_token_minus(t_token *token)
{
	t_token	*last_token;

	last_token = ft_split_tokens(token);
	ft_update_tokens(last_token);
}
