/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:06:37 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/21 19:48:14 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_minishell" initializes all the fields of the `t_minishell` 
 * structure, including setting up file descriptors, environment variables, and
 * other necessary fields for the shell to operate.
 *  
 * @param char **envp				An array of strings representing the 
 * 									system's environment variables. This is 
 * 									used to initialize the linked list of
 * 									environment variables within the 
 * 									`minishell` structure.
 * 
 * The function "ft_init_envp" initializes the `minishell.env` field with a 
 * NULL-terminated array of strings, where each element is initialized to NULL. 
 * It counts the number of elements in the linked list `minishell.list_envp`, 
 * then allocates memory for an array of strings of that size.
 * 
 * @param t_minishell minishell		A structure containing a linked list of 
 * 									environment variables (`list_envp`). This 
 * 									is used to determine how many elements are 
 * 									needed for the `envp` array
 * 
 */
/*static void	ft_init_envp(t_minishell *minishell, char **envp)
{
	int		i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
		i++;
	minishell->envp = (char **)malloc((i + 1) * sizeof(char *));
	if (!minishell->envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		minishell->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	minishell->envp[i] = NULL;
}*/

void	ft_init_minishell(t_minishell *minishell)
{
	minishell->list_envp = ft_init_list_envp(minishell->envp);
	minishell->dirprompt = NULL;
	minishell->stdin = dup(STDIN_FILENO);
	minishell->stdout = dup(STDOUT_FILENO);
	minishell->line = NULL;
	minishell->tokens = NULL;
	minishell->exit = 0;
	ft_dirprompt(minishell);
}
