/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:40:17 by pabromer          #+#    #+#             */
/*   Updated: 2024/11/28 17:00:16 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "split_substrings" splits an input string into quoted and 
 * unquoted substrings, processes each substring, and joins the processed 
 * substrings into a final result.
 * 
 * - Handles both quoted and unquoted substrings, ensuring quotes are preserved 
 *   where necessary.
 * - Uses helper functions to extract and process substrings, including 
 *   variable expansion.
 * - Handles a maximum of 100 substrings, each up to 256 characters in length.
 * 
 * @param t_minishell *minishell	A pointer to the shell's state structure.
 * @param char *input				The input string to be split and processed.
 * 
 * @return char*					A dynamically allocated string containing 
 *									the final processed result after splitting 
 *									and joining substrings.
 * 
 * The function "process_substrings" processes all substrings extracted from 
 * the input string. It trims double quotes, handles variable expansion, and 
 * processes single-quoted substrings through `process_substrings_else`.
 * 
 * - Iterates through each substring and processes it based on its content.
 * - Handles special cases for substrings containing `$` for variable 
 *   expansion.
 * - Frees allocated memory for trimmed substrings when no longer needed.
 * 
 * @param t_minishell *minishell	A pointer to the shell's state structure.
 * @param char *substring_ptrs[100]	An array of pointers to substrings for
 * 									processing.
 * 
 * The function "process_substrings_else" handles processing of substrings 
 * that are not enclosed in double quotes. It trims single quotes from the 
 * substring or expands variables if the substring contains a `$` character.
 * 
 * - Trims single quotes and replaces the substring with the trimmed version.
 * - Expands variables using `ft_split_expand` if `$` is present in the 
 *   substring.
 * 
 * @param t_minishell *minishell	A pointer to the shell's state structure.
 * @param char *substring_ptrs[100]	An array of pointers to substrings for 
 * 									processing.
 * @param int i						The index of the current substring to 
 * 									process.
 * @param char *trim				A pointer to the trimmed substring.
 * 
 * The function "extract_unquoted" extracts a substring not enclosed in quotes
 * from the input string. It stops at any whitespace or quote character and 
 * copies the content into a buffer.
 * 
 * - Skips whitespace and quotes.
 * - Copies the unquoted content into the `substrings` array.
 * - Advances the input pointer to the next unprocessed character.
 * 
 * @param char **start				A pointer to the current position in the 
 * 									input string.
 * @param int *size					A pointer to the current size of the 
 * 									`substrings` array.
 * @param char substrings[100][256]	A 2D array to store extracted substrings.
 * 
 * @return char*					A pointer to the newly extracted substring,
 * 									or `NULL` 
 *									if the content exceeds the buffer size.
 * 
 */

/*static char	*extract_unquoted(char **start, int *size, \
char substrings[100][256])
{
	char	*end;
	size_t	len;

	end = *start;
	while (*end && *end != '"' && *end != '\'' && *end != ' ' && *end != '\t')
		end++;
	len = end - *start;
	if (len >= 256)
		return (NULL);
	ft_strcpy(substrings[*size], *start);
	substrings[*size][len] = '\0';
	*start = end;
	return (substrings[(*size)++]);
}

static void	process_substrings_else(t_minishell *minishell, \
char *substring_ptrs[100], int i, char *trim)
{
	free(trim);
	trim = ft_strtrim(substring_ptrs[i], "\'");
	if (ft_strcmp(trim, substring_ptrs[i]) != 0)
		substring_ptrs[i] = ft_strdup(trim);
	else
	{
		if (ft_strchr(substring_ptrs[i], '$'))
			substring_ptrs[i] = ft_split_expand(minishell, substring_ptrs[i]);
	}
}

static void	process_substrings(t_minishell *minishell, \
char *substring_ptrs[100])
{
	int		i;
	char	*trim;

	i = 0;
	while (substring_ptrs[i])
	{
		trim = ft_strtrim(substring_ptrs[i], "\"");
		if (ft_strcmp(trim, substring_ptrs[i]) != 0)
		{
			if (ft_strchr(trim, '$'))
				substring_ptrs[i] = ft_split_expand(minishell, trim);
			else
				substring_ptrs[i] = trim;
		}
		else
			process_substrings_else(minishell, substring_ptrs, i, trim);
		i++;
	}
}

static void	ft_cpy_substr(char substrings[100][256], \
char *substring_ptrs[100], int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		substring_ptrs[i] = substrings[i];
		i++;
	}
}

char	*split_substrings(t_minishell *minishell, char *input)
{
	char	substrings[100][256];
	char	*substring_ptrs[100];
	int		size;
	char	*start;

	size = 0;
	start = input;
	while (*start)
	{
		if (size >= 100)
			break ;
		if (*start == '"' || *start == '\'')
			extract_quoted(&start, &size, substrings);
		else if (*start != ' ' && *start != '\t')
			extract_unquoted(&start, &size, substrings);
		else
			start++;
	}
	ft_cpy_substr(substrings, substring_ptrs, size);
	process_substrings(minishell, substring_ptrs);
	return (ft_split_expand_join(substring_ptrs));
}*/
