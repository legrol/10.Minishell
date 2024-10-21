/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:06:37 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/10/21 12:35:39 by pabromer         ###   ########.fr       */
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
 * static char **ft_init_envp(t_minishell minishell)
 * 						
 * 						In order to initialize minishell.env with NULL. This
 * 						function creates a double malloc NULL with the same number
 *						of secundary malloc as list_envp number of elements. 
 * 
 */
static char **ft_init_envp(t_minishell minishell)
{
	t_envp	*temp;
	char	**init_env;	
	int		i;

	i = 0;
	temp = minishell.list_envp;
	while (minishell.list_envp)
	{
		i++;
		minishell.list_envp = minishell.list_envp->next;
	}
	minishell.list_envp = temp;
	init_env = (char **)malloc((i + 1) * sizeof(char *));
	if(!init_env)
		return (NULL);
	i = 0;
	temp = minishell.list_envp;
	while(minishell.list_envp)
	{
		init_env[i] = NULL;
		minishell.list_envp = minishell.list_envp->next;
		i++;
	}
	init_env[i] = NULL;
	return (init_env);
}


t_minishell	ft_init_minishell(char **envp)
{
	t_minishell	minishell;
	
	/*minishell = (t_minishell *)malloc(sizeof(t_minishell));
	if (!minishell)
		return (NULL);*/
	//minishell = NULL;
	minishell.list_envp = ft_init_list_envp(envp);
	/*if (!minishell.list_envp)
	{
		free(minishell);
		return (NULL);
	}*/
	minishell.dirprompt = NULL;
	minishell.envp = ft_init_envp(minishell);
	minishell.stdin = dup(STDIN_FILENO);
	minishell.stdout = dup(STDOUT_FILENO);
	minishell.line = NULL;
	minishell.tokens = NULL;
	minishell.exit = 0;
	ft_dirprompt(&minishell);
	return (minishell);
}
