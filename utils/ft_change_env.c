/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:53:36 by pabromer          #+#    #+#             */
/*   Updated: 2024/11/05 11:48:42 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_envp	*new_node_envp(char *key, char *value)
{
	t_envp	*new_node;

	new_node = (t_envp *)malloc(sizeof(t_envp));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (!value)
		new_node->value = NULL;
	else
		new_node->value = ft_strdup(value);
	new_node->next = NULL;	
	return (new_node);
}

void	ft_change_env(t_minishell *minishell, const char *str1, \
		const char *str2)
{
	t_envp	*temp;
	t_envp  *new_node;
	
	if (!str1)
		return ;
	temp = minishell->list_envp;
	while (minishell->list_envp)
	{
		if (ft_strcmp(minishell->list_envp->key, (char *)str1) == 0)
		{
			if (minishell->list_envp->value)
				free(minishell->list_envp->value);
			if (str2)
				minishell->list_envp->value = ft_strdup(str2);
			else
				minishell->list_envp->value = NULL;
			minishell->list_envp = temp;
			return ;
		}
		minishell->list_envp = minishell->list_envp->next;
	}
	new_node = new_node_envp((char *)str1, (char *)str2);
	new_node->next = temp;
	minishell->list_envp = new_node;
}
