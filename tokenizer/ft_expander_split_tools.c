/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_split_tools.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-28 11:54:55 by rdel-olm          #+#    #+#             */
/*   Updated: 2024-11-28 11:54:55 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
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
