/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dirprompt1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-20 14:27:24 by rdel-olm          #+#    #+#             */
/*   Updated: 2024-11-20 14:27:24 by rdel-olm         ###   ########.fr       */
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

void	ft_dirprompt(t_minishell	*minishell)
{
	char	cwd[1024];
	char	*temp;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("Current working directory: %s\n", cwd);
		temp = ft_strjoin("minishell: ", cwd);
		if (!temp)
		{
			perror("Error allocating moemroy for temp");
			return ;
		}
		if (minishell->dirprompt)
		{
			printf("Freeing old dirprompt: %s\n", minishell->dirprompt);
			free(minishell->dirprompt);
		}
		minishell->dirprompt = ft_strjoin(temp, "$ ");
		if (!minishell->dirprompt)
		{
			perror("Error allocating memory for dirprompt");
			free(temp);
			return ;
		}
		printf("Final dirprompt: %s\n", minishell->dirprompt);
		free(temp);
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
