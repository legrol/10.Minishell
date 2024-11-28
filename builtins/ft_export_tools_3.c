/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_tools_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-28 11:07:51 by rdel-olm          #+#    #+#             */
/*   Updated: 2024-11-28 11:07:51 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_count_lines" counts the number of environment variables
 * in the minishell environment list.
 *
 * - Iterates through the linked list `minishell->list_envp` and increments 
 *   a counter for each node.
 * - Restores the original position of `minishell->list_envp` after counting.
 * - Returns the total number of environment variables in the list.
 *
 * @param t_minishell *minishell A pointer to the minishell structure 
 * 								 containing 
 *                               the environment list.
 *
 * @return int The number of environment variables in the list. 
 * 
 */

int	ft_count_lines(t_minishell *minishell)
{
	t_envp	*temp;
	int		i;

	i = 0;
	temp = minishell->list_envp;
	while (minishell->list_envp)
	{
		i++;
		minishell->list_envp = minishell->list_envp->next;
	}
	minishell->list_envp = temp;
	return (i);
}
