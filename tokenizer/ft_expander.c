/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:04:17 by pabromer          #+#    #+#             */
/*   Updated: 2024/11/26 16:39:56 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * 
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
 * The function "ft_split_expand_join" joins an array of substrings into a 
 * single string. It dynamically allocates memory for the result and ensures 
 * memory is freed for intermediate steps.
 * 
 * - Iterates through the array of substrings (`split`), joining them one by 
 *   one.
 * - Frees the previously allocated memory for intermediate results.
 * 
 * - Example:
 *   Input: `split = {"echo", " ", "$USER"}`
 *   Output: `"echo $USER"`
 * 
 * @param char **split	An array of strings to be joined.
 * 
 * @return char*		A dynamically allocated string containing the 
 * 						concatenated substrings, or `NULL` if memory 
 * 						allocation fails.
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
 * The function "ft_count_dollar" counts the occurrences of the `$` character 
 * in a string and calculates the total size needed to prepare the string for 
 * splitting. It adds additional space for inserting newlines after each `$`.
 * 
 * - Iterates through the string, counting occurrences of `$`.
 * - Returns the total length of the string plus the count of `$` characters, 
 *   plus one for the null terminator.
 * 
 * @param char *s	The input string to analyze.
 * 
 * @return int		The total size required to prepare the string for splitting.
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
 * The function "ft_only_expand_join" retrieves the appropriate value for 
 * expansion based on the shell's state or environment variables.
 * 
 * - If `f == 1`, it expands `$?` using the shell's last exit status.
 * - Otherwise, it searches for the variable in the environment.
 * 
 * @param t_minishell *minishell	The shell's state structure.
 * @param char *join				The variable name to expand.
 * @param int f						Flag indicating special expansion for `$?`.
 * 
 * @return char*					A dynamically allocated string containing 
 *									the expanded value or `NULL` if not found.
 * 
 * The function "ft_only_expand_join" retrieves the appropriate value for 
 * expansion based on the shell's state or environment variables.
 * 
 * - If `f == 1`, it expands `$?` using the shell's last exit status.
 * - Otherwise, it searches for the variable in the environment.
 * 
 * @param t_minishell *minishell	The shell's state structure.
 * @param char *join				The variable name to expand.
 * @param int f						Flag indicating special expansion for `$?`.
 * 
 * @return char*					A dynamically allocated string containing 
 *									the expanded value or `NULL` if not found.
 * 
 * The function "ft_change_token" creates a new token by joining a temporary 
 * string and a special substring, ensuring proper memory management.
 * 
 * - If `temp` is `NULL`, it duplicates `sp` directly.
 * - Frees memory for `temp`, `join`, and `sp` to avoid memory leaks.
 * 
 * @param char *temp	A temporary string used in the join process.
 * @param char *sp		A substring or special string to append.
 * 
 * @return char*		A new dynamically allocated string containing the 
 * 						result.
 * 
 * The function "ft_find_special_char" searches for the first non-alphanumeric
 * character in a given string `s` that is not an underscore (`_`).
 * 
 * - If no special character is found, it returns `'\0'`.
 * - Used to identify delimiters for variable expansion in the shell.
 * 
 * @param char *s	The input string to search for special characters.
 * 
 * @return char		The first special character found or `'\0'` if none exists.
 * 
 */

static char	ft_find_special_char(char *s)
{
	int	i;

	if (!s)
		return ('\0');
	i = 0;
	while (s[i])
	{
		if (ft_isalnum(s[i]) == 0 && s[i] != '_')
			return (s[i]);
		i++;
	}
	return ('\0');
}

static char	*ft_change_token(char *temp, char *sp)
{
	char	*t;
	char	*join;

	if (!temp)
		join = ft_strdup(sp);
	else
		join = ft_strjoin(temp, sp);
	t = ft_strdup(join);
	if (temp)
		free(temp);
	free(join);
	free(sp);
	return (t);
}

static char	*ft_only_expand_join(t_minishell *minishell, char *join, int f)
{
	char	*temp;

	if (f == 1)
		temp = ft_itoa(minishell->exit);
	else
	{
		if (ft_find_dir(minishell, join))
			temp = ft_strdup(ft_find_dir(minishell, join));
		else
			temp = NULL;
	}
	return (temp);
}

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

static int	ft_count_dollar(char *s)
{
	int	c;
	int	i;

	i = 0;
	c = 0;
	while (s[i])
	{
		if (s[i] == '$')
			c++;
		i++;
	}
	return (i + c + 1);
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

char	*ft_split_expand_join(char **split)
{
	char	*temp;
	char	*temp2;
	int		i;

	temp = split[0];
	i = 1;
	while (split[i])
	{
		temp2 = ft_strjoin(temp, split[i]);
		free(temp);
		temp = temp2;
		i++;
	}
	i = 0;
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
	int		i;

	i = 1;
	temp = minishell->tokens;
	while (minishell->tokens)
	{
		if (ft_strchr(minishell->tokens->token_value, '$') \
		|| ft_strchr(minishell->tokens->token_value, '\"') \
		|| ft_strchr(minishell->tokens->token_value, '\''))
			ft_expander_action(minishell);
		i++;
		minishell->tokens = minishell->tokens->next;
	}
	minishell->tokens = temp;
	ft_print_tokens(minishell->tokens);
}
