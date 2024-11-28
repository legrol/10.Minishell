/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-28 09:58:05 by rdel-olm          #+#    #+#             */
/*   Updated: 2024-11-28 09:58:05 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_swap_pwd" updates the `PWD` and `OLDPWD` environment
 * variables in the shell. It sets `OLDPWD` to the previous working directory 
 * and attempts to update `PWD` to the current working directory using 
 * `getcwd`.
 * If `getcwd` fails, it constructs a fallback prompt using the previous 
 * directory.
 * 
 * - Updates the prompt (`dirprompt`) after changing the directory.
 * 
 * @param t_minishell *minishell	A pointer to the shell's state structure, 
 *									which contains environment variables and 
 *									the current prompt.
 * 
 * @param char *pwd					A string representing the previous working 
 *									directory (`OLDPWD`). * 
 * 
 */

void	ft_swap_pwd(t_minishell *minishell, char *pwd)
{
	char	cwd[1024];
	char	*temp;

	ft_change_env(minishell, "OLDPWD", pwd);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_change_env(minishell, "PWD", cwd);
		ft_dirprompt(minishell);
	}
	else
	{
		temp = ft_strjoin(PROMPT, pwd);
		minishell->dirprompt = ft_strjoin(temp, "/..$ ");
		free (temp);
	}
}
