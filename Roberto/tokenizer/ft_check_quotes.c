/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-17 09:56:43 by rdel-olm          #+#    #+#             */
/*   Updated: 2024-10-17 09:56:43 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_checker_quotes_unclosed" checks if the current line
 * in the t_minishell structure has any unclosed quotes (single or double).
 * It calls the "ft_checker_quotes" function to determine if the line
 * contains unclosed quotes.
 * 
 * @param t_minishell *minishell	A pointer to the minishell structure that
 * 									contains the line to be checked.
 * 
 * @return int						Returns 1 if there are unclosed quotes,
 *									otherwise returns 0.
 * 
 * The function "ft_checker_quotes" checks if there are any unclosed 
 * quotes (either single quotes or double quotes) in the provided line of 
 * text.
 * It iterates through the given string, updating a flag when it encounters
 * an opening or closing quote, and returns the status of quotes at the end.
 * 
 * @param char *line	The string to be checked for unclosed quotes.
 * @param int lenght	The length of the string to be checked.
 * 
 * @return int			Returns 0 if all quotes are properly closed.
 *						Returns 1 if there's an unclosed single quote.
 *						Returns 2 if there's an unclosed double quote.
 * 
 */

int	ft_checker_quotes(char	*line, int lenght)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (line[i] && i < lenght)
	{
		if (line[i] == '\'' && flag == 0)
			flag = 1;
		else if (line[i] == '\"' && flag == 0)
			flag = 2;
		else if (line[i] == '\'' && flag == 1)
			flag = 0;
		else if (line[i] == '\"' && flag == 2)
			flag = 0;
		i++;
	}
	return (flag);
}

int	ft_checker_quotes_unclosed(t_minishell *minishell)
{
	if (ft_checker_quotes(minishell->line, ft_strlen(minishell->line)) != 0)
	{
		ft_putendl_fd(QUOTES_ERR, STDERR_FILENO);
		return (1);
	}
	return (0);
}
