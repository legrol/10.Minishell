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
 * The function "ft_init_envp" duplicates the environment variables (`envp`) 
 * into the `minishell->envp` array, ensuring that each string is copied 
 * dynamically and can be independently freed.
 * 
 * - Calls "ft_start_init_envp" to allocate memory for the environment array.
 * - Iterates through the input `envp`, duplicating each string using 
 *   `ft_strdup`.
 * - Handles memory allocation failures by freeing already-allocated memory 
 *   and returning an error message.
 * - Sets the `dirprompt` field of the `t_minishell` structure to `NULL` for 
 *   further initialization.
 * 
 * @param t_minishell *minishell	A pointer to the shell's state structure, 
 *									where the copied environment array will be 
 *									stored.
 * 
 * @param char **envp				A pointer to the original environment 
 *									variables array.
 * 
 * @return void						This function does not return a value, but 
 *									it updates the `t_minishell` structure or 
 *									prints an error message if a failure 
 *									occurs.
 * 
 * The function "ft_start_init_envp" initializes the environment variables 
 * (`envp`) array in the `t_minishell` structure by allocating memory for a 
 * copy of the given `envp`.
 * 
 * - It counts the number of strings in the input `envp` array.
 * - Allocates enough memory to store a copy of the input array, including 
 *   space for a `NULL` terminator.
 * - Returns `-1` if memory allocation fails or if `envp` is `NULL`.
 * 
 * This function is a preparatory step for duplicating the environment 
 * variables in the `ft_init_envp` function.
 * 
 * @param t_minishell *minishell	A pointer to the shell's state structure, 
 *									where the copied environment array will be
 *									stored.
 * 
 * @param char **envp				A pointer to the original environment 
 *									variables array.
 * 
 * @return int						Returns `0` on success, or `-1` if the 
 *									input `envp` is `NULL` or memory allocation
 *									fails.
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
