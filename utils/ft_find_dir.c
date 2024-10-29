/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:53:36 by pabromer          #+#    #+#             */
/*   Updated: 2024/10/29 08:59:13 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_find_dir(t_minishell *minishell, const char *str)
{
	char	*result;
	t_envp	*temp;

	temp = minishell->list_envp;
	while (minishell->list_envp)
	{
		if (ft_strcmp(minishell->list_envp->key, (char *)str) == 0)
		{
			result = minishell->list_envp->value;
			minishell->list_envp = temp;
			return (result);
		}
		minishell->list_envp = minishell->list_envp->next;
	}
	minishell->list_envp = temp;
	return (NULL);
}
