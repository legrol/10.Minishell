/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:06:37 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/25 22:15:27 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_init_minishell" initializes the fields of the `t_minishell` 
 * structure, setting up the shell's state for execution. It ensures that all 
 * fields are properly initialized with default values or dynamically allocated 
 * resources.
 * 
 * - Initializes the environment variable linked list (`list_envp`) using 
 *   the `ft_init_list_envp` function.
 * - Sets the `dirprompt` field to `NULL`. This will be updated later by 
 *   `ft_dirprompt` to reflect the current working directory.
 * - Creates copies of the standard input and output file descriptors 
 *   (`stdin` and `stdout`) using `dup`, ensuring the shell can restore them 
 *   if necessary.
 * - Sets other fields (`line`, `tokens`) to `NULL` to indicate they are empty 
 *   or uninitialized at startup.
 * - Sets the `exit` field to `0`, representing a successful execution state.
 * - Initializes the `terminal_status` field to `1`, which may indicate that 
 *   the shell is ready for terminal interaction.
 * - Calls `ft_dirprompt` to set up the prompt string based on the current 
 *   working directory.
 * 
 * This function ensures the `t_minishell` structure is fully prepared for use 
 * in the shell's main loop.
 * 
 * @param t_minishell *minishell	A pointer to the `t_minishell` structure 
 *									to be initialized.
 * 
 * @return void						This function does not return a value.
 * 
 */

void	ft_init_minishell(t_minishell *minishell)
{
	minishell->list_envp = ft_init_list_envp(minishell->envp);
	minishell->dirprompt = NULL;
	minishell->stdin = dup(STDIN_FILENO);
	minishell->stdout = dup(STDOUT_FILENO);
	minishell->line = NULL;
	minishell->tokens = NULL;
	minishell->exit = 0;
	minishell->terminal_status = 1;
	ft_dirprompt(minishell);
}
