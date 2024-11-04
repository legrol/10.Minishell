/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-04 12:16:24 by rdel-olm          #+#    #+#             */
/*   Updated: 2024-11-04 12:16:24 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_token_size" calculates the size of a token in the input 
 * line, considering special characters (`>`, `<`, `|`), quoted strings, 
 * and ensuring that double characters (`>>`, `<<`) are treated as a single 
 * token.
 * 
 * @param char *line			The input line containing the token to be 
 *								measured.
 * @param int *index			A pointer to the current position in the line, 
 *								which will be updated during the calculation.
 * @return int					The size of the token.
 * 
 */

int	ft_token_size(char *line, int *index)
{
	int		i;
	char	c;

	i = 0;
	c = 32;
	while (line[*index + i] && (line[*index + i] != 32 || c != 32))
	{
		if (line[*index + i] == '"' || line[*index + i] == '\'')
		{
			c = line[*index + i];
			i++;
		}
		else if (ft_strchr("<>|", line[*index + i]))
		{
			if (line[*index + i] == '>' || line[*index + i] == '<')
			{
				if (line[*index + i] == line[*index + i + 1])
					return (2);
			}
			return (1);
		}
		i++;
	}
	return (i);
}
