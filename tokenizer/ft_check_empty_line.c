/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_empty_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-06 12:13:47 by rdel-olm          #+#    #+#             */
/*   Updated: 2024-11-06 12:13:47 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_check_empty_line" xxx
 * 
 * @param char *line				xxx
 * @param t_minishell *minishell	xxx
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

void	ft_check_empty_line(char *line, t_minishell *minishell)
{
	if (!line || *line == '\0' || ft_only_spaces(line))
	{
		ft_dirprompt(minishell);
		ft_putstr_fd(minishell->dirprompt, STDERR);
		minishell->exit = 1;
		return ;
	}
}

// void	ft_check_empty_line(char *line, t_minishell *minishell)
// {
// 	if (!line)
// 	{
// 		fprintf(stderr, "Error: line es NULL\n");
// 		return ;
// 	}
// 	if (*line == '\0')
// 	{
// 		fprintf(stderr, "Error: line está vacío\n");
// 		return ;
// 	}
// 	if (ft_only_spaces(line))
// 	{
// 		fprintf(stderr, "Solo se detectaron espacios\n");
// 		// ft_dirprompt(minishell);
// 		// if (minishell->dirprompt == NULL)
// 		// {
// 		// 	fprintf(stderr, "Error: minishell->dirprompt es NULL\n");
// 		// 	return ;
// 		// }
// 		// ft_putstr_fd(minishell->dirprompt, STDERR);
// 		// minishell->exit = 1;
// 		return ;
// 	}
// }

