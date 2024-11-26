/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:33:21 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/26 16:58:14 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_syntax_error" validates the syntax of the token list in the 
 * `t_minishell` structure. It ensures that no syntax-sensitive tokens (e.g., 
 * operators or delimiters) appear at invalid positions.
 * 
 * - Checks the following conditions:
 *   - The first token in the list cannot be a syntax-sensitive token.
 *   - Consecutive syntax-sensitive tokens are not allowed.
 *   - The last token in the list cannot be a syntax-sensitive token.
 * - If a syntax error is detected, it calls `ft_print_syntax_error` to handle 
 *   the error and return `-1`.
 * - If no errors are found, the function returns the count of tokens.
 * 
 * @param t_minishell *minishell	A pointer to the `t_minishell` structure,
 *									which contains the list of tokens and 
 *									the current shell state.
 * 
 * @return int						Returns `-1` if a syntax error is detected, 
 *									or the number of tokens if the syntax is 
 *									valid.
 * 
 * The function "ft_token_type" checks whether a given token type corresponds 
 * to a syntax-sensitive token (e.g., operators or delimiters).
 * 
 * - Returns `1` if the token type matches predefined syntax-sensitive types 
 *   (1, 2, 3, 4, 8).
 * - Returns `0` otherwise.
 * 
 * @param int token					An integer representing the type of token 
 *									to be checked.
 * 
 * @return int						Returns `1` for syntax-sensitive tokens, 
 *									or `0` otherwise.
 * 
 * The function "ft_check_token_value" validates the value of a given token to 
 * determine if it introduces a syntax error. It checks for sequences of dots 
 * (e.g., `...`) and validates their placement relative to previous tokens.
 * 
 * - Returns `1` if the token's value contains only dots and is preceded by a 
 *   syntax-sensitive token or is the first token in the list.
 * - Returns `0` otherwise.
 * 
 * @param t_token *token			 A pointer to the token to be checked.
 * 
 * @return int						Returns `1` if the token's value is 
 * 									invalid, or `0` if it is valid.
 * 
 */

static int	ft_print_syntax_error(t_minishell *minishell, t_token *temp)
{
	ft_printf("Syntax error\n");
	minishell->tokens = temp;
	minishell->exit = 1;
	free(minishell->line);
	return (-1);
}

static int	ft_token_type(int token)
{
	if (token == 1 || token == 2 || token == 3 || token == 4 || token == 8)
		return (1);
	return (0);
}

static int	ft_check_token_value(t_token *token)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (token->token_value[i])
	{
		if (token->token_value[i] == '.')
			j++;
		i++;
	}
	if (i != 0 && i == j && (!token->prev || token->prev->token_type == 1 \
	|| token->prev->token_type == 2 || token->prev->token_type == 3 \
	|| token->prev->token_type == 4 || token->prev->token_type == 8))
		return (1);
	return (0);
}

int	ft_syntax_error(t_minishell *minishell)
{
	int		i;
	t_token	*temp;

	temp = minishell->tokens;
	i = 0;
	while (minishell->tokens)
	{
		if (i == 0 && ft_token_type(minishell->tokens->token_type) == 1)
			return (ft_print_syntax_error(minishell, temp));
		else if (minishell->tokens->next && \
		ft_token_type(minishell->tokens->token_type) == 1 \
		&& ft_token_type(minishell->tokens->next->token_type) == 1)
			return (ft_print_syntax_error(minishell, temp));
		else if (!minishell->tokens->next && \
		ft_token_type(minishell->tokens->token_type) == 1)
			return (ft_print_syntax_error(minishell, temp));
		else if (ft_check_token_value(minishell->tokens) == 1)
			return (ft_print_syntax_error(minishell, temp));
		i++;
		minishell->tokens = minishell->tokens->next;
	}
	minishell->tokens = temp;
	return (i);
}
