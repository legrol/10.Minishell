/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dirprompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:27:24 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/26 16:37:06 by pabromer         ###   ########.fr       */
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

// void	ft_dirprompt(t_minishell	*minishell)
// {
// 	char	cwd[1024];
// 	char	*temp;

// 	if (getcwd(cwd, sizeof(cwd)) != NULL)
// 	{
// 		temp = ft_strjoin("minishell: ", cwd);
// 		if (!temp)
// 		{
// 			perror("Error allocating memory for temp");
// 			return ;
// 		}
// 		if (minishell->dirprompt)
// 		{
// 			free(minishell->dirprompt);
// 			minishell->dirprompt = NULL;
// 		}
// 		minishell->dirprompt = ft_strjoin(temp, "$ ");
// 		free(temp);
// 		if (!minishell->dirprompt)
// 		{
// 			perror("Error allocating memory for dirprompt");
// 			return ;
// 		}
// 	}
// 	else
// 	{
// 		perror("getcwd() error");
// 		if (minishell->dirprompt)
// 		{
// 			free(minishell->dirprompt);
// 			minishell->dirprompt = NULL;
// 		}
// 	}
// }

void	ft_dirprompt(t_minishell *minishell)
{
	char	cwd[1024];
	char	*temp;
	char	*new_prompt;

	temp = NULL;
	new_prompt = NULL;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		temp = ft_strjoin("minishell: ", cwd);
		if (!temp)
		{
			perror("Error allocating memory for temp");
			return ;
		}
		new_prompt = ft_strjoin(temp, "$ ");
		free(temp);
		if (!new_prompt)
		{
			perror("Error allocating memory for new_prompt");
			return ;
		}
		if (minishell->dirprompt)
			free(minishell->dirprompt);
		minishell->dirprompt = new_prompt;
	}
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
