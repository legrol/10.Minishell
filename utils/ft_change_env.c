/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:53:36 by pabromer          #+#    #+#             */
/*   Updated: 2024/10/24 19:01:33 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_change_env(t_minishell *minishell, const char *str1, \
		const char *str2)
{
	t_envp	*temp;

	temp = minishell->list_envp;
	while (minishell->list_envp)
	{
		if (ft_strcmp(minishell->list_envp->key, (char *)str1) == 0)
		{
			free(minishell->list_envp->value);
			minishell->list_envp->value = ft_strdup(str2);
			minishell->list_envp = temp;
			return ;
		}
		minishell->list_envp = minishell->list_envp->next;
	}
	minishell->list_envp = temp;
}
