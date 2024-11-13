/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_envp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:33:21 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/13 12:05:19 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * 
 * ft_init_envp(t_minishell *minishell, char **envp) before to init minishell we want to init the env that works in case we want to open a new minishell in minishell.
 * 
 * static int	ft_start_init_envp(t_minishell *minishell, char **envp) to reserve the memory for the env.
 * 
 */


static int	ft_start_init_envp(t_minishell *minishell, char **envp)
{
	int		i;

	i = 0;
	if (!envp)
		return (-1);
	while (envp[i])
		i++;
	minishell->envp = (char **)malloc((i + 1) * sizeof(char *));
	if (!minishell->envp)
		return (-1);
	return (0);
}
void	ft_init_envp(t_minishell *minishell, char **envp)
{
	int		i;

	i = 0;
	if (ft_start_init_envp(minishell, envp) == -1)
	{
		ft_putstr_fd("Error: Unable to allocate memory for envp\n", STDERR);
		return ;
	}
	while (envp[i])
	{
		minishell->envp[i] = ft_strdup(envp[i]);
		if (!minishell->envp[i])
		{
			while (i > 0)
				free(minishell->envp[--i]);
			free(minishell->envp);
			minishell->envp = NULL;
			ft_putstr_fd("Error: Memory allocation failure in envp\n", STDERR);
			return ;
		}
		i++;
	}
	minishell->envp[i] = NULL;
	minishell->dirprompt = NULL;
}

