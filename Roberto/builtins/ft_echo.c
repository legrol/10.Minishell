/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-02 11:36:47 by rdel-olm          #+#    #+#             */
/*   Updated: 2024-10-02 11:36:47 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * 
 * 
 * 
 */

void	ft_echo(char *input)
{
	char	*shorting;
	char	**splited;

	shorting = ft_strnstr(input, "echo ", ft_strlen(input));
	splited = ft_split(shorting, ' ');
	if (splited[1][0] == '-' && splited[1][1] == 'n' && splited[1][2] == '\0')
		ft_printf("%s", splited[2]);
	else
		ft_printf("%s\n", splited[1]);
	p_freessplit(splited, p_mallocsize(shorting, ' '));
}
