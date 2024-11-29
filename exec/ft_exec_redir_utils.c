/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_redir_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-29 15:14:23 by rdel-olm          #+#    #+#             */
/*   Updated: 2024-11-29 15:14:23 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_contains_invalid_chars" checks whether the input string 
 * contains any invalid or unwanted control characters, specifically escape 
 * sequences such as `\033[?2004h`. These sequences are typically related to 
 * terminal modes that can interfere with normal processing.
 * 
 * @param const char *line			The input string to be checked for 
 * 									invalid characters.
 * @return int						Returns 1 if invalid characters are found,
 * 									or 0 otherwise.
 * 
 * The function "ft_try_dup2_out" redirects the standard output (STDOUT) to 
 * the specified file descriptor (`fd`) if the `minishell->redout` flag 
 * indicates that output redirection has not already been set. It updates 
 * the `redout` flag to prevent further duplications.
 * 
 * @param t_minishell *minishell	A pointer to the minishell structure that
 * 									contains the state of the redirection.
 * @param int fd					The file descriptor to which STDOUT will 
 * 									be redirected.
 * @return void
 * 
 */

void	ft_try_dup2_out(t_minishell *minishell, int fd)
{
	if (minishell->redout == -1)
	{
		dup2(fd, STDOUT_FILENO);
		minishell->redout = 1;
	}
}

int	ft_contains_invalid_chars(const char *line)
{
	return (ft_strnstr(line, "\033[?2004h", ft_strlen(line)) != NULL \
	|| ft_strnstr(line, "\033[?2004h", ft_strlen(line)) != NULL);
}
