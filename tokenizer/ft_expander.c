/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:04:17 by pabromer          #+#    #+#             */
/*   Updated: 2024/11/29 01:23:27 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_expander" iterates through all tokens in the minishell
 * structure, expanding any tokens that contain special characters such as
 * single quotes, double quotes, or dollar signs. It updates the token values
 * in place with their expanded forms.
 * 
 * @param t_minishell *minishell    A pointer to the minishell structure, which
 *                                  contains the list of tokens to process.
 * @return void                     This function does not return a value, but
 *                                  modifies the token list within `minishell`.
 * 
 * The function "ft_expander_action" expands a token's value by processing
 * special characters such as single quotes, double quotes, and dollar signs.
 * It dynamically constructs the expanded token value based on the specific
 * processing rules for each special character.
 * 
 * @param t_minishell *minishell    A pointer to the minishell structure, used
 *                                  to access environment variables and other
 *                                  data during expansion.
 * @param t_token *token            A pointer to the token being processed.
 * @return void                     This function does not return a value, but
 *                                  modifies the `token->token_value` field.
 * 
 * The function "ft_handle_single_quotes" processes segments enclosed in single
 * quotes within a token. It extracts the literal content and appends it to the
 * new token value, ignoring the single quotes themselves.
 * 
 * @param const char *token_value   The value of the token being processed.
 * @param int *i                    A pointer to the current index within
 *                                  `token_value`.
 * @param char **new_value          A pointer to the new token value under
 *                                  construction.
 * @param int *new_size             A pointer to the current size of 
 *                                  `new_value`.
 * @return void                     This function does not return a value, but
 *                                  modifies `new_value` and `new_size`.
 * 
 */

static void	ft_handle_single_quotes(const char *token_value, int *i, \
char **new_value, int *new_size)
{
	int		start;
	char	*segment;

	start = ++(*i);
	while (token_value[*i] && token_value[*i] != '\'')
		(*i)++;
	segment = ft_substr(token_value, start, *i - start);
	*new_size += ft_strlen(segment);
	*new_value = ft_realloc(*new_value, *new_size - ft_strlen(segment) - 1, \
	*new_size);
	ft_memmove(*new_value + ft_strlen(*new_value), segment, \
	ft_strlen(segment));
	free(segment);
	if (token_value[*i] == '\'')
		(*i)++;
}

static void	ft_expander_action(t_minishell *minishell, t_token *token)
{
	char	*new_value;
	int		new_size;
	int		i;

	new_value = ft_calloc(1, 1);
	new_size = 1;
	i = 0;
	while (token->token_value[i])
	{
		if (token->token_value[i] == '\'')
			ft_handle_single_quotes(token->token_value, &i, &new_value, \
			&new_size);
		else if (token->token_value[i] == '\"')
			ft_handle_double_quotes(minishell, token->token_value, &i, \
			&new_value);
		else if (token->token_value[i] == '$')
			ft_handle_dollar_sign(minishell, token->token_value, &i, \
			&new_value);
		else
			ft_handle_literal_segment(token->token_value, &i, &new_value);
	}
	free(token->token_value);
	token->token_value = new_value;
}

void	ft_expander(t_minishell *minishell)
{
	t_token	*temp;

	temp = minishell->tokens;
	while (minishell->tokens)
	{
		if (ft_strchr(minishell->tokens->token_value, '$') || \
			ft_strchr(minishell->tokens->token_value, '\"') || \
			ft_strchr(minishell->tokens->token_value, '\''))
		{
			ft_expander_action(minishell, minishell->tokens);
		}
		minishell->tokens = minishell->tokens->next;
	}
	minishell->tokens = temp;
	ft_print_tokens(minishell->tokens);
}
