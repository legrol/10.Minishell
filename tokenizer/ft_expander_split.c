/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/11/25 15:01:15 by pabromer         ###   ########.fr       */
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
 * The function "extract_quoted" extracts a substring enclosed in quotes 
 * (single or double) from the input string. It copies the quoted content, 
 * including the enclosing quotes, into a buffer and advances the input 
 * pointer.
 * 
 * - Searches for the closing quote that matches the opening quote.
 * - Copies the quoted content into the `substrings` array, ensuring it fits 
 *   within the defined buffer size.
 * - Updates the input pointer to continue parsing after the closing quote.
 * 
 * @param char **start				A pointer to the current position in the 
 * 									input string.
 * @param int *size					A pointer to the current size of the 
 * 									`substrings` array.
 * @param char substrings[100][256]	A 2D array to store extracted substrings.
 * 
 * @return char*					A pointer to the newly extracted substring,
 * 									or `NULL` 
 *									if the quote is not closed or the content
 *									exceeds the buffer size.
 * 
 */

char	*extract_quoted(char **start, int *size, char substrings[100][256])
{
	char	quote;
	char	*end;
	size_t	len;

	quote = **start;
	end = ++(*start);
	while (*end && *end != quote)
		end++;
	if (*end != quote)
		return (NULL);
	len = end - *start + 2;
	if (len >= 256)
		return (NULL);
	substrings[*size][0] = quote;
	ft_strcpy(&substrings[*size][1], *start);
	substrings[*size][len - 1] = quote;
	substrings[*size][len] = '\0';
	*start = end + 1;
	return (substrings[(*size)++]);
}

char	*extract_unquoted(char **start, int *size, char substrings[100][256])
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

void	process_substrings_else(t_minishell *minishell, \
char *substring_ptrs[100], int i, char *trim)
{
	char	*expanded;

	//free(trim);
	trim = ft_strtrim(substring_ptrs[i], "\'");
	if (ft_strcmp(trim, substring_ptrs[i]) != 0)
		substring_ptrs[i] = trim;
	else if (ft_strchr(substring_ptrs[i], '$'))
	{
		expanded = ft_split_expand(minishell, substring_ptrs[i]);
		substring_ptrs[i] = expanded;
	}
	free(trim);
}

void	process_substrings(t_minishell *minishell, char *substring_ptrs[100])
{
	int		i;
	char	*trim;

	i = 0;
	while (substring_ptrs[i])
	{
		trim = ft_strtrim(substring_ptrs[i], "\"");
		if (ft_strcmp(trim, substring_ptrs[i]) != 0)
		{
			//free(substring_ptrs[i]);
			substring_ptrs[i] = ft_strchr(trim, '$') ?
				ft_split_expand(minishell, trim) : trim;
		}
		else
			process_substrings_else(minishell, substring_ptrs, i, trim);
		if (trim)
			free(trim);
		i++;
	}
}

/*char *join_substrings(char *substring_ptrs[100]) 
{
	char *result;
	char *temp;

	result = substring_ptrs[0];
	for (int i = 1; substring_ptrs[i]; i++) {
		temp = ft_strjoin(result, substring_ptrs[i]);
		free(result);
		result = temp;
		//free(substring_ptrs[i]);
	}
	return result;
}*/

char *split_substrings(t_minishell *minishell, char *input)
{
	static char	substrings[100][256];
	static char	*substring_ptrs[100];
	int			size;
	char		*start;
	int			i;

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
	i = 0;
	while (i < size)
	{
		substring_ptrs[i] = substrings[i];
		i++;
	}
	process_substrings(minishell, substring_ptrs);
	return (ft_split_expand_join(substring_ptrs));
}
