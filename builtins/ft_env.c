/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:38:51 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/10/18 10:31:54 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_env" prints all the environment variables currently stored
 * in the shell's environment list. It iterates through the linked list of
 * environment variables (`list_envp`), and for each variable with a non-null 
 * value, it prints the key-value pair in the format `key=value`.
 * 
 * - The function temporarily stores the head of the list (`temp`) to ensure 
 *   the list's structure remains unchanged after traversal.
 * - If an environment variable does not have a value (i.e., `value == NULL`), 
 *   it is skipped and not printed.
 * 
 * @param t_minishell *minishell	A pointer to the `t_minishell` structure
 *									that holds the linked list of environment 
 *									variables (`list_envp`).
 * 
 * @return void						This function does not return a value. 
 * 
 */

void	ft_env(t_minishell *minishell)
{
	t_envp	*temp;

	temp = minishell->list_envp;
	while (minishell->list_envp)
	{
		if (minishell->list_envp->value)
			ft_printf("%s=%s\n", minishell->list_envp->key, \
			minishell->list_envp->value);
		minishell->list_envp = minishell->list_envp->next;
	}
	minishell->list_envp = temp;
}
