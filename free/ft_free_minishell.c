/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:23:05 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/10/29 20:12:27 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_free_minishell" xxx
 * 
 * @param t_minishell *minishell		xxx
 * 
 * 
 */

void	ft_free_minishell(t_minishell *minishell)
{
	int i;
		
	i = 0;
	if (minishell->envp)
	{
		while (minishell->envp[i])
			free(minishell->envp[i++]);
		free(minishell->envp);
	}
	free(minishell->dirprompt);
	ft_free_envp_list(minishell->list_envp);
	ft_free_tokens(minishell->tokens);
	free(minishell->line);
}
