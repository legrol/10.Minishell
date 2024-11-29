/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_tools_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-29 11:35:27 by rdel-olm          #+#    #+#             */
/*   Updated: 2024-11-29 11:35:27 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_handle_literal_segment" processes a literal segment within
 * a token that does not contain special characters (`$`, `'`, or `"`). The
 * segment is appended to the new token value.
 * 
 * @param const char *token_value   The token value being processed.
 * @param int *i                    A pointer to the current index within
 *                                  `token_value`.
 * @param char **new_value          A pointer to the new token value under
 *                                  construction.
 * @return void                     This function does not return a value but
 *                                  modifies `new_value`.
 * 
 * The function "ft_advance_to_special_char" advances the index within a token
 * until a special character (`$`, `'`, or `"`) or the end of the token is
 * reached.
 * 
 * @param const char *token_value   The token value being processed.
 * @param int *i                    A pointer to the current index within
 *                                  `token_value`.
 * @return void                     This function does not return a value but
 *                                  modifies `i`.
 * 
 * The function "ft_realloc" reallocates memory for a given pointer (`p`) to a
 * new size, copying the original data to the new memory block. If the new size
 * is smaller, it truncates the data; if larger, it ensures uninitialized
 * memory is zeroed.
 * 
 * @param void *p                   The pointer to the memory block to resize.
 * @param int old_size              The size of the original memory block.
 * @param int new_size              The size of the new memory block.
 * @return void*                    A pointer to the reallocated memory block,
 *                                  or NULL if the new size is zero.
 * 
 * The function "ft_append_to_new_value" appends a string (`to_append`) to the
 * end of a dynamically allocated string (`new_value`). It reallocates memory 
 * for `new_value` as needed to accommodate the new data.
 * 
 * @param char **new_value          A pointer to the string being constructed.
 * @param const char *to_append     The string to append to `new_value`.
 * @return void                     This function does not return a value but
 *                                  modifies `new_value`.
 * 
 */

void	ft_append_to_new_value(char **new_value, const char *to_append)
{
	size_t	old_len;
	size_t	append_len;
	size_t	new_len;

	old_len = ft_strlen(*new_value);
	append_len = ft_strlen(to_append);
	new_len = old_len + append_len + 1;
	*new_value = ft_realloc(*new_value, old_len, new_len);
	ft_memmove(*new_value + old_len, to_append, append_len);
	(*new_value)[new_len - 1] = '\0';
}

void	*ft_realloc(void *p, int old_size, int new_size)
{
	void	*r;

	if (!new_size)
		return (free(p), NULL);
	r = ft_calloc(1, new_size);
	if (p && old_size <= new_size)
		ft_memmove(r, p, old_size);
	else if (p && old_size > new_size)
		ft_memmove(r, p, new_size);
	return (free(p), r);
}

static void	ft_advance_to_special_char(const char *token_value, int *i)
{
	while (token_value[*i] && token_value[*i] != '$' && token_value[*i] \
	!= '\'' && token_value[*i] != '\"')
		(*i)++;
}

void	ft_handle_literal_segment(const char *token_value, int *i, \
char **new_value)
{
	int		start;

	start = *i;
	ft_advance_to_special_char(token_value, i);
	ft_append_to_new_value(new_value, ft_substr(token_value, start, *i \
	- start));
}
