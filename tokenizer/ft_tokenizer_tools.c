/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-28 12:28:07 by rdel-olm          #+#    #+#             */
/*   Updated: 2024-11-28 12:28:07 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_handle_special_char" processes special characters at the 
 * start of a token. It checks for `>>` or `<<` and tokenizes them as a 
 * single token. If neither is found, it handles a single character like `>`, 
 * `<`, or `|`.
 * 
 * @param t_token *token		A pointer to the token structure being filled.
 * @param char *line			The input line containing the characters to be 
 *								processed.
 * @param int *index			A pointer to the current position in the line, 
 *								which will be updated as characters are 
 * 								processed.
 * @param int i					The current position in the token's value.
 * @return int					The updated position in the token's value.
 * 
 * The function "ft_fill_token" fills the token structure with the value 
 * extracted from the input line.
 *
 * @param t_token *token			A pointer to the token structure to be 
 *									filled with the extracted value.
 * @param char *line				A string representing the input line from 
 *									which the token is extracted.
 * @param int *index				A pointer to the current position in the 
 *									line.
 * 
 */

int	ft_handle_special_char(t_token *token, char *line, \
int *index, int i)
{
	if (i == 0 && (line[*index] == '>' || line[*index] == '<') \
	&& line[*index] == line[*index + 1])
	{
		token->token_value[i++] = line[(*index)++];
		token->token_value[i++] = line[(*index)++];
	}
	else if (i == 0)
		token->token_value[i++] = line[(*index)++];
	return (i);
}

static int	ft_handle_quotes(t_token *token, char *line, int *index, int i)
{
	char	c;

	c = line[(*index)++];
	token->token_value[i++] = c;
	while (line[*index] && line[*index] != c)
		token->token_value[i++] = line[(*index)++];
	if (line[*index] == c)
		token->token_value[i++] = line[(*index)++];
	return (i);
}

void	ft_fill_token(t_token *token, char *line, int *index)
{
	int		i;
	char	c;

	i = 0;
	c = 32;
	while (line[*index] && (line[*index] != 32 || c != 32))
	{
		if ((line[*index] == '"' || line[*index] == '\'') && c == 32)
		{
			i = ft_handle_quotes(token, line, index, i);
			c = 32;
		}
		else if (ft_strchr("<>|", line[*index]))
		{
			i = ft_handle_special_char(token, line, index, i);
			break ;
		}
		else
			token->token_value[i++] = line[(*index)++];
	}
	token->token_value[i] = '\0';
}
