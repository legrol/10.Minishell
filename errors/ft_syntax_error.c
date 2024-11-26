/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:33:21 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/20 09:27:47 by pabromer         ###   ########.fr       */
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
 * The function "ft_token_type" determines whether a given token type 
 * corresponds to a syntax-sensitive token (e.g., operators or delimiters).
 * 
 * - Returns `1` for specific token types (e.g., 1, 2, 3, 4, 8).
 * - Returns `0` for all other token types.
 * 
 * @param int token					An integer representing the type of token 
 *									to be checked.
 * 
 * @return int						Returns `1` if the token is 
 * 									syntax-sensitive, or `0` otherwise.
 * 
 * The function "ft_print_syntax_error" prints a generic syntax error message 
 * and updates the shell's state to indicate an error. It restores the original 
 * token list (`temp`) and sets the shell's exit status to `1`.
 * 
 * - This function is called when a syntax error is detected during the parsing
 *   or validation of tokens.
 * 
 * @param t_minishell *minishell	A pointer to the `t_minishell` structure,
 *									which contains the list of tokens and 
 *									the current shell state.
 * 
 * @param t_token *temp				A pointer to the head of the original token 
 *									list, which is restored before returning.
 * 
 * @return int						Always returns `-1` to indicate a syntax 
 *									error has occurred.
 * 
 */

static int	ft_print_syntax_error(t_minishell *minishell, t_token *temp)
{
	ft_printf("Syntax error\n");
	minishell->tokens = temp;
	minishell->exit = 1;
	return (-1);
}

static int	ft_token_type(int token)
{
	if (token == 1 || token == 2 || token == 3 || token == 4 || token == 8)
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
		i++;
		minishell->tokens = minishell->tokens->next;
	}
	minishell->tokens = temp;
	return (i);
}
