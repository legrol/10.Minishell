/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:04:17 by pabromer          #+#    #+#             */
/*   Updated: 2024/11/27 10:21:59 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_expander" processes all tokens in the shell, expanding 
 * variables and handling special cases like quoted content.
 * 
 * - Iterates through the token list and processes each token with `$`, 
 *   single quotes, or double quotes.
 * - Calls `ft_expander_action` to handle individual token expansion.
 * 
 * @param t_minishell *minishell	The shell's state structure.
 * 
 * The function "ft_expander_action" processes a single token, handling 
 * variable expansion based on its content and context (e.g., quotes).
 * 
 * - Expands variables if `$` is found and the token is not quoted.
 * - Uses `split_substrings` for tokens requiring additional processing.
 * 
 * @param t_minishell *minishell	The shell's state structure.
 * 
 * The function "ft_split_expand" handles splitting a string into substrings 
 * based on `$` and expands each variable found.
 * 
 * - Uses `ft_prepare_split` to format the string with newlines for splitting.
 * - Expands variables using `ft_only_expand` for substrings containing `$`.
 * - Joins the processed substrings into a final result.
 * 
 * @param t_minishell *minishell	The shell's state structure.
 * @param char *s					The input string to process.
 * 
 * @return char*					A dynamically allocated string with all 
 *									variables expanded.
 * 
 * The function "ft_prepare_split" processes a string by adding newlines 
 * (`'\n'`) after each `$` character, preparing it for splitting into 
 * substrings.
 * 
 * - Allocates memory based on the size calculated by `ft_count_dollar`.
 * - Iterates through the input string, copying characters into the new buffer.
 * - Inserts a newline (`'\n'`) after each `$` character to facilitate 
 *   splitting.
 * 
 * - Example:
 *   Input: `"echo $USER"`
 *   Output: `"echo\n$USER"`
 * 
 * @param char *s	The input string to process.
 * 
 * @return char*	A dynamically allocated string with newlines inserted, 
 * 					or `NULL` if memory allocation fails. 
 * 
 * The function "ft_only_expand" handles the expansion of variables in a string.
 * 
 * - Extracts the portion of the string starting with `$` and identifies 
 *   special characters as delimiters.
 * - Expands `$?` using the shell's exit status or retrieves the corresponding 
 *   environment variable.
 * - Combines the expanded value with the rest of the string.
 * 
 * @param t_minishell *minishell	The shell's state structure.
 * @param char *s					The input string containing variables to
 * 									expand.
 * 
 * @return char*					A dynamically allocated string with the 
 * 									expanded value. 
 * 
 */

static char	*ft_only_expand(t_minishell *minishell, char *s)
{
	char	*temp;
	char	*join;
	char	*sp;
	char	a;
	int		f;

	f = 0;
	temp = ft_strchr_exp(s, '$');
	a = ft_find_special_char(temp);
	temp = ft_strdup(temp);
	if (temp && temp[0] == '?')
	{
		f = 1;
		sp = ft_strchr_exp(temp, '?');
	}
	else
		sp = ft_strchr(temp, a);
	sp = ft_strdup(sp);
	join = ft_strtrim(temp, sp);
	free(temp);
	temp = ft_only_expand_join(minishell, join, f);
	free (join);
	return (ft_change_token(temp, sp));
}

static char	*ft_prepare_split(char *s)
{
	int		c;
	int		i;
	char	*temp;

	temp = malloc(ft_count_dollar(s) * sizeof(char));
	i = 0;
	c = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			temp[c + i] = '\n';
			c++;
		}
		temp[c + i] = s[i];
		i++;
	}
	temp[c + i] = '\0';
	return (temp);
}

char	*ft_split_expand(t_minishell *minishell, char *s)
{
	char	*temp;
	char	**split;
	char	*temp2;
	int		i;

	temp = ft_prepare_split(s);
	split = ft_split(temp, '\n');
	i = 0;
	while (split[i])
	{
		if (ft_strchr(split[i], '$'))
		{
			temp2 = ft_only_expand(minishell, split[i]);
			free(split[i]);
			split[i] = temp2;
		}
		i++;
	}
	if (temp)
		free(temp);
	temp = ft_split_expand_join(split);
	free(split);
	return (temp);
}

static void	ft_expander_action(t_minishell *minishell)
{
	char	*t;

	if (ft_strchr(minishell->tokens->token_value, '$') \
		&& !ft_strchr(minishell->tokens->token_value, '\"') \
		&& !ft_strchr(minishell->tokens->token_value, '\''))
	{
		t = ft_split_expand(minishell, minishell->tokens->token_value);
		free(minishell->tokens->token_value);
		minishell->tokens->token_value = ft_strdup(t);
		free(t);
	}
	else
	{
		t = split_substrings(minishell, minishell->tokens->token_value);
		free(minishell->tokens->token_value);
		minishell->tokens->token_value = ft_strdup(t);
		free(t);
	}
}

void	ft_expander(t_minishell *minishell)
{
	t_token	*temp;

	temp = minishell->tokens;
	while (minishell->tokens)
	{
		if (ft_strchr(minishell->tokens->token_value, '$') \
		|| ft_strchr(minishell->tokens->token_value, '\"') \
		|| ft_strchr(minishell->tokens->token_value, '\''))
			ft_expander_action(minishell);
		minishell->tokens = minishell->tokens->next;
	}
	minishell->tokens = temp;
	ft_print_tokens(minishell->tokens);
}
