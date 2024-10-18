/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-17 13:31:22 by rdel-olm          #+#    #+#             */
/*   Updated: 2024-10-17 13:31:22 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_skip_spaces" advances the index in the given string "line"
 * to skip any whitespace characters. It handles spaces (ASCII 32) as well
 * as other whitespace characters like tabs, newlines, carriage returns, etc.
 * 
 * 
 * @param char *line	The input string where spaces are being skipped.
 * @param int *index	A pointer to the integer index that indicates the
 *						current position in the string. The function will
 *						increment the index to skip over any whitespace 
 * 						characters. 
 * 						The value pointed to by this index will be updated 
 * 						in place.
 * 
 */

void	ft_skip_spaces(char *line, int *index)
{
	while (line[*index] == 32 || (line[*index] >= 9 && line[*index] <= 13))
		(*index)++;
}
