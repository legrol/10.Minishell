/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dirprompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:37:37 by pabromer          #+#    #+#             */
/*   Updated: 2024/10/16 10:48:29 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_dirprompt" updates the value of dirprompt in minishell
 * structure
 *
 *  
 * 
 * @param char cwd[1024]	A string wich contains the working directory.
 * 
 * 
 * @param char *temp		A temporary string to join the PROMPT 
 * 							and the working directory.  
 */

void	ft_dirprompt(t_minishell	*minishell)
{
	char	cwd[1024];
	char	*temp;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		temp = ft_strjoin(PROMPT, cwd);
		minishell->dirprompt = ft_strjoin(temp, "$ ");
		free (temp);
	}
	else
	{
		perror("getcwd() error");
		minishell->dirprompt = NULL;
	}
}