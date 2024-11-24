/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_empty_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:13:47 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/24 17:17:19 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_check_empty_line" verifies if the current line in the 
 * minishell structure is empty or contains only whitespace. If true, it 
 * sets the exit status to 1 and avoids further processing.
 * 
 * @param t_minishell *minishell	A pointer to the t_minishell structure, 
 * 									which contains information about the 
 * 									current state, including the line to be 
 * 									checked and the exit status.
 * 
 * The function "ft_only_spaces" checks if a given string contains only
 * whitespace characters (spaces).
 * 
 * @param line 						A constant character pointer representing 
 * 									the line to check.
 * 
 * @return 							Returns 1 if the line only contains spaces,
 * 									or 0 otherwise.
 * 
 */

static int	ft_only_spaces(const char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] != '\0')
	{
		if (line[i] != 32)
			return (0);
		i++;
	}
	return (1);
}

void	ft_check_empty_line(t_minishell *minishell)
{
	char	*line;

	if (minishell->line)
	{
		line = minishell->line;
		if (!line || *line == '\0' || ft_only_spaces(line) == 0)
		{
			minishell->exit = 1;
			return ;
		}
	}
}
