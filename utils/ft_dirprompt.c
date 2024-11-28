/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dirprompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:27:24 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/28 13:25:29 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_dirprompt" updates the value of dirprompt in minishell
 * structure
 * 
 * @param char cwd[1024]	A string wich contains the working directory.
 * 
 * @param char *temp		A temporary string to join the PROMPT 
 * 							and the working directory.  
 * 
 */

static char	*ft_dirprompt_if(t_minishell *minishell, char cwd[1024])
{
	char	*new_prompt;
	char	*temp;

	temp = NULL;
	new_prompt = NULL;
	temp = ft_strjoin("minishell: ", cwd);
	if (!temp)
	{
		perror("Error allocating memory for temp");
		return (NULL);
	}
	new_prompt = ft_strjoin(temp, "$ ");
	free(temp);
	if (!new_prompt)
	{
		perror("Error allocating memory for new_prompt");
		return (NULL);
	}
	if (minishell->dirprompt)
		free(minishell->dirprompt);
	return (new_prompt);
}

void	ft_dirprompt(t_minishell *minishell)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		minishell->dirprompt = ft_dirprompt_if(minishell, cwd);
	else
	{
		perror("getcwd() error");
		if (minishell->dirprompt)
		{
			free(minishell->dirprompt);
			minishell->dirprompt = NULL;
		}
	}
}
