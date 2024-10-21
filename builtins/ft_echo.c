/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:36:47 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/10/21 11:42:29 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * 
 * FALTA liberar el split
*/

static int	ft_echo_only(t_minishell *minishell)
{
	char *trim;

	trim = ft_strtrim(minishell->line, " ");
	if (ft_strcmp(trim, "echo") == 0)
	{
		printf("\n");
		free(trim);
		return (1);
	}
	free(trim);
	return (0);
}

static void ft_print_echo(char *str, char c, t_minishell *minishell)
{
	char *trim;

	if (ft_strchr(str, '\''))
	{
		trim = ft_strtrim(str, "\'");
		if (ft_strcmp(trim, "$?") == 0)
			ft_printf("%i%c", minishell->exit, c);
		else 
			ft_printf("%s%c", trim, c);
	}
	else 
	{
		trim = ft_strtrim(str, "\"");
		if (ft_strcmp(trim, "$?") == 0)
			ft_printf("%i%c", minishell->exit, c);
		else 
			ft_printf("%s%c", trim, c);
	}
	free(trim);
}

void	ft_echo(t_minishell *minishell)
{
	char	*shorting;
	char	**splited;

	if (ft_echo_only(minishell) == 1)
		return;
	shorting = ft_strnstr(minishell->line, "echo ", ft_strlen(minishell->line));
	splited = ft_split_m(shorting, ' ');
	if (splited[1][0] == '-' && splited[1][1] == 'n' && splited[1][2] == '\0' && !splited[2])
		ft_printf("");
	else if (splited[1][0] == '-' && splited[1][1] == 'n' && splited[1][2] == '\0' && splited[2])
		ft_print_echo(splited[2], '\0', minishell);
	else
		ft_print_echo(splited[1], '\n', minishell);
	//freessplit_m(splited, mallocsize_m(shorting, ' '));
}
