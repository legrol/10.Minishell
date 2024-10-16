/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:35:33 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/10/16 12:54:02 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_cd(t_minishell *minishell)
{
	char **split;
	char cwd[1024];
		
	split = ft_split(minishell->line, ' ');
	if (split[2])
		ft_printf("bash: cd: too many arguments\n");
	else if ((split[1][0] == '~' && split[1][1] == '\0'))
		chdir(ft_find_dir(minishell, "HOME"));
	else if (!split[1])
		chdir(ft_find_dir(minishell, "HOME"));
	else if(chdir(split[1]) != 0)
		ft_printf("bash: cd: %s: No such file or directory\n", split[1]);
	else
	{
		ft_change_env(minishell, "OLDPWD", ft_find_dir(minishell, "PWD"));
		chdir(split[1]);
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			ft_change_env(minishell, "PWD", cwd);
		else
			perror("getcwd() error");
	}
	ft_dirprompt(minishell);
}
