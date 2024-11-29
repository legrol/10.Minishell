/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 00:07:55 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/29 00:08:23 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_handle_double_quotes" processes double quotes within a
 * token. It handles the expansion of variables (`$`) while preserving literal
 * text and ignores the enclosing double quotes.
 * 
 * @param t_minishell *minishell    A pointer to the minishell structure, used
 *                                  for variable expansion.
 * @param const char *token_value   The token value containing the double
 *                                  quotes.
 * @param int *i                    A pointer to the current index within
 *                                  `token_value`.
 * @param char **new_value          A pointer to the new token value under
 *                                  construction.
 * @return void                     This function does not return a value but
 *                                  modifies `new_value`.
 * 
 * The function "ft_handle_literal_in_quotes" extracts a literal segment within
 * double quotes and appends it to the new token value. The segment ends when
 * a dollar sign (`$`) or another double quote (`"`) is encountered.
 * 
 * @param const char *token_value   The token value containing the literal
 *                                  segment.
 * @param int *i                    A pointer to the current index within
 *                                  `token_value`.
 * @param char **new_value          A pointer to the new token value under
 *                                  construction.
 * @return void                     This function does not return a value but
 *                                  modifies `new_value`.
 * 
 * The function "ft_handle_dollar_sign" processes a dollar sign (`$`) within
 * a token. It handles the expansion of special cases like `$?` for the exit
 * status or environment variables starting with `$`.
 * 
 * @param t_minishell *minishell    A pointer to the minishell structure, used
 *                                  for environment variable lookup and exit
 *                                  status retrieval.
 * @param const char *token_value   The token value containing the dollar sign.
 * @param int *i                    A pointer to the current index within
 *                                  `token_value`.
 * @param char **new_value          A pointer to the new token value under
 *                                  construction.
 * @return void                     This function does not return a value but
 *                                  modifies `new_value`.
 * 
 * The function "ft_expand_variable" expands a shell variable referenced by
 * a dollar sign (`$`) and appends its value to the new token value. If the
 * variable exists in the environment, its value is appended; otherwise, 
 * nothing is appended.
 * 
 * @param t_minishell *minishell    A pointer to the minishell structure, used
 *                                  to look up environment variables.
 * @param const char *token_value   The token value containing the variable
 *                                  name to expand.
 * @param int *i                    A pointer to the current index within
 *                                  `token_value`.
 * @param char **new_value          A pointer to the new token value under
 *                                  construction.
 * @return void                     This function does not return a value but
 *                                  modifies `new_value`.
 * 
 * The function "ft_expand_status" appends the exit status of the minishell
 * process to the new token value. The status is converted from an integer to
 * a string before appending.
 * 
 * @param t_minishell *minishell    A pointer to the minishell structure, which
 *                                  contains the current exit status.
 * @param char **new_value          A pointer to the new token value under
 *                                  construction.
 * @return void                     This function does not return a value but
 *                                  modifies `new_value`.
 * 
 */

static void	ft_expand_status(t_minishell *minishell, char **new_value)
{
	char	*status_str;

	status_str = ft_itoa(minishell->exit);
	ft_append_to_new_value(new_value, status_str);
	free(status_str);
}

static void	ft_expand_variable(t_minishell *minishell, const \
char *token_value, int *i, char **new_value)
{
	int		start;
	char	*var_name;
	char	*env_value;

	start = *i;
	while (token_value[*i] && (ft_isalnum(token_value[*i]) || \
	token_value[*i] == '_'))
		(*i)++;
	var_name = ft_substr(token_value, start, *i - start);
	env_value = ft_find_dir(minishell, var_name);
	free(var_name);
	if (env_value)
		ft_append_to_new_value(new_value, env_value);
}

void	ft_handle_dollar_sign(t_minishell *minishell, \
const char *token_value, int *i, char **new_value)
{
	(*i)++;
	if (token_value[*i] == '?')
	{
		(*i)++;
		ft_expand_status(minishell, new_value);
	}
	else
		ft_expand_variable(minishell, token_value, i, new_value);
}

static void	ft_handle_literal_in_quotes(const char *token_value, int *i, \
char **new_value)
{
	int		start;
	char	*literal;

	start = *i;
	while (token_value[*i] && token_value[*i] != '$' && token_value[*i] != '\"')
		(*i)++;
	literal = ft_substr(token_value, start, *i - start);
	ft_append_to_new_value(new_value, literal);
	free(literal);
}

void	ft_handle_double_quotes(t_minishell *minishell, const char \
*token_value, int *i, char **new_value)
{
	(*i)++;
	while (token_value[*i] && token_value[*i] != '\"')
	{
		if (token_value[*i] == '$')
			ft_handle_dollar_sign(minishell, token_value, i, new_value);
		else
			ft_handle_literal_in_quotes(token_value, i, new_value);
	}
	if (token_value[*i] == '\"')
		(*i)++;
}
