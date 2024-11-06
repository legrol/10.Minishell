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

void	ft_check_empty_line(char *line, t_minishell *minishell)
{
	if (!line || *line == '\0')
	{
		ft_dirprompt(minishell);
		ft_putstr_fd(minishell->dirprompt, STDERR);
		minishell->exit = 1;
		return ;
	}
}
