/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:37:36 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/10/17 17:44:43 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int ft_count_lines(t_minishell *minishell)
{
	t_envp *temp;
	int		i;

	i = 0;
	temp = minishell->list_envp;
	while(minishell->list_envp->next)
	{
		i++;
		minishell->list_envp = minishell->list_envp->next;
	}
	minishell->list_envp = temp;
	return (i);
}

static char **ft_copy_env(t_minishell *minishell)
{
	t_envp *temp;
	char	**cpy;
	int i;

	cpy = (char **)ft_calloc((ft_count_lines(minishell)+1),sizeof(char*));
	if (!cpy)
		return (NULL);
	temp = minishell->list_envp;
	i = 0;
	while(minishell->list_envp->next)
	{
		cpy[i] = ft_strdup(minishell->list_envp->key);
		i++;
		minishell->list_envp = minishell->list_envp->next;
	}
	cpy[i] = NULL;
	minishell->list_envp = temp;
	return (cpy);
}
static char **ft_sort_print(t_minishell *minishell)
{
	char	**cpy;
	int		i;
	char	*temp;

	cpy = ft_copy_env(minishell);
	i = 0;
	while(cpy[i+1])
	{
		if (ft_strcmp(cpy[i], cpy[i+1]) > 0)
		{
			temp = cpy[i+1];
			cpy[i+1] = cpy[i];
			cpy[i] = temp;
			i = -1;
		}
		i++;
	}
	return (cpy);
}
static int ft_export_only(t_minishell *minishell)
{
	char	**cpy;
	int		i;
	t_envp	*temp;
	char 	*trim;

	trim = ft_strtrim(minishell->line, " ");
	if (ft_strcmp(trim, "export") == 0)
	{
		cpy = ft_sort_print(minishell);
		temp = minishell->list_envp;
		i = 0;
		while(cpy[i+1])
		{
			while (ft_strcmp(cpy[i], minishell->list_envp->key) != 0)
				minishell->list_envp = minishell->list_envp->next;
			ft_printf("declare -x %s=\"%s\"\n", minishell->list_envp->key, \
			minishell->list_envp->value);
			free(cpy[i]);
			minishell->list_envp = temp;
			i++;
		}
		free(cpy[i]);
		free(cpy[i+1]);
		minishell->list_envp = temp;
		free(cpy);
		free(trim);
		return (1);
	}
	free(trim);
	return (0);
}

void ft_export(t_minishell *minishell)
{
	t_envp *temp;
	
	if (ft_export_only(minishell) == 1)
		return ;
}

