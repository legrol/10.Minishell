/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:38:51 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/10/16 12:11:55 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_minishell *minishell)
{
	t_envp	*temp;

	temp = minishell->list_envp;
	while (minishell->list_envp)
	{
		ft_printf("%s=%s\n", minishell->list_envp->key, \
		minishell->list_envp->value);
		minishell->list_envp = minishell->list_envp->next;
	}
	minishell->list_envp = temp;
}
