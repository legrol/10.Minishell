/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:35:33 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/10/31 16:02:36 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * static void ft_swap_pwd;
 * 
 * FALTA IMPLEMENTAR ~/blablabla
 * FALTA liberar el split
 * FALTA añadir los codigos de error
*/

static void	ft_swap_pwd(t_minishell *minishell)
{
	char	cwd[1024];
	char	*temp;

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

static void	ft_cd_only(t_minishell *minishell)
{
	chdir(ft_find_dir(minishell, "HOME"));
	ft_swap_pwd(minishell);
}

static void	ft_try_cd(t_minishell *minishell, t_ast *ast, int i)
{
	if (i > 2)
	{
		minishell->exit = 1;
		ft_printf("bash: cd: too many arguments\n");
	}
	else if (strcmp(ast->value, "~") == 0)
	{
		chdir(ft_find_dir(minishell, "HOME"));
		ft_swap_pwd(minishell);
	}
	else if (strcmp(ast->value, "-") == 0)
	{
		chdir(ft_find_dir(minishell, "OLDPWD"));
		ft_printf("%s\n", ft_find_dir(minishell, "OLDPWD"));
		ft_swap_pwd(minishell);
	}
	else if (chdir(ast->value) != 0)
	{
		minishell->exit = 1;
		ft_printf("bash: cd: %s: No such file or directory\n", ast->value);
	}
	else
		ft_swap_pwd(minishell);
}

void	ft_cd(t_minishell *minishell, t_ast *ast)
{
	int i;
	t_ast *temp;

	i = 1;
	temp = ast;
	while (ast->left)
	{
		i++;
		ast = ast->left;
	}
	minishell->exit = 0;
	if (i == 1)
	{
		ft_cd_only(minishell);
		ast = temp;
		return ;
	}
	ft_try_cd(minishell, ast, i);
	ast = temp;
}
