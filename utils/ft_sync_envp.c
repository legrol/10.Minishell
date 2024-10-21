/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sync_envp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:48:00 by pabromer          #+#    #+#             */
/*   Updated: 2024/10/21 14:37:37 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char **ft_init_envp(t_minishell *minishell)
{
	t_envp	*temp;
	char	**init_env;	
	int		i;

	i = 0;
	temp = minishell->list_envp;
	while (minishell->list_envp)
	{
		i++;
		minishell->list_envp = minishell->list_envp->next;
	}
	minishell->list_envp = temp;
	init_env = (char **)malloc((i + 1) * sizeof(char *));
	if(!init_env)
		return (NULL);
	i = 0;
	temp = minishell->list_envp;
	while(minishell->list_envp)
	{
		init_env[i] = NULL;
		minishell->list_envp = minishell->list_envp->next;
		i++;
	}
	init_env[i] = NULL;
	return (init_env);
}

static void ft_free_envp(t_minishell *minishell)
{
	int i;

	i = 0;
	while(minishell->envp[i])
	{
		free(minishell->envp[i]);
		i++;
	}
	free(minishell->envp);
}

void ft_sync_envp(t_minishell *minishell)
{
	t_envp 	*temp;
	char	*join;
	char	**new_envp;
	int		i;

	i = 0;
	temp = minishell->list_envp;
	new_envp = ft_init_envp(minishell);
	if(minishell->envp)
		ft_free_envp(minishell);
	minishell->envp = new_envp;
	while(minishell->list_envp)
	{
		join = ft_strjoin(minishell->list_envp->key, "=");
		if (minishell->envp[i])
			free(minishell->envp[i]);
		minishell->envp[i] = ft_strjoin(join, minishell->list_envp->value);
		free(join);
		i++;
		minishell->list_envp = minishell->list_envp->next; 
	}
	minishell->envp[i] = NULL;
	minishell->list_envp = temp;
}
