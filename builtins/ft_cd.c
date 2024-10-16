/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:35:33 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/10/16 15:39:45 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * static void ft_swap_pwd;
 * 
 * FALTA IMPLEMETAR si solo cd que envie a HOME
 * FALTA IMPLEMENTAR ~/blablabla
*/

static void ft_swap_pwd(t_minishell *minishell)
{
	char cwd[1024];
	char *temp;

	ft_change_env(minishell, "OLDPWD", ft_find_dir(minishell, "PWD"));
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_change_env(minishell, "PWD", cwd);
		ft_dirprompt(minishell);
	}
	else
	{
		temp = ft_strjoin(PROMPT, ft_find_dir(minishell, "PWD"));
		minishell->dirprompt = ft_strjoin(temp, "/..$ ");
		free (temp);
	}
}

void ft_cd(t_minishell *minishell)
{
	char **split;
	int i;

	i = 0;
	split = ft_split_m(minishell->line, ' ');
	if (split[2])
		ft_printf("bash: cd: too many arguments\n");
	else if ((split[1][0] == '~' && split[1][1] == '\0'))
	{
		chdir(ft_find_dir(minishell, "HOME"));
		ft_swap_pwd(minishell);
	}
	else if ((split[1][0] == '-' && split[1][1] == '\0'))
	{
		chdir(ft_find_dir(minishell, "OLDPWD"));
		ft_printf("%s\n", ft_find_dir(minishell, "OLDPWD"));
		ft_swap_pwd(minishell);
	}
	else if(chdir(split[1]) != 0)
		ft_printf("bash: cd: %s: No such file or directory\n", split[1]);
	else
		ft_swap_pwd(minishell);
}
