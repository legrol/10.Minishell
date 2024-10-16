/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:06:37 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/10/16 10:53:52 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_minishell.c" initializes the members of the t_minishell
 * structure.
 *  
 * @param char **envp	An array of strings representing the system environment
 * 						variables, usually passed as the second argument to 
 * 						the main function. This value is used to initialize 
 * 						the list of environment variables in the t_minishell 
 * 						structure. 
 * 
 * 
 * 
 */

t_minishell	*ft_init_minishell(char **envp)
{
	t_minishell	*minishell;
	
	minishell = (t_minishell *)malloc(sizeof(t_minishell));
	if (!minishell)
		return (NULL);
	minishell->list_envp = ft_init_list_envp(envp);
	if (!minishell->list_envp)
	{
		free(minishell);
		return (NULL);
	}
	minishell->envp = envp;
	minishell->stdin = dup(STDIN_FILENO);
	minishell->stdout = dup(STDOUT_FILENO);
	minishell->line = NULL;
	minishell->tokens = NULL;
	minishell->exit = 0;
	ft_dirprompt(minishell);
	return (minishell);
}
