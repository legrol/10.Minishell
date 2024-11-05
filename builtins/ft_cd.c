/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:35:33 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/05 11:35:15 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * static void ft_swap_pwd;
 * 
*/

static void	ft_swap_pwd(t_minishell *minishell, char *pwd)
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

static void	ft_cd_only(t_minishell *minishell, t_ast *ast, int i, char *pwd)
{
	if (i == 1)
	{
		if (chdir(ft_find_dir(minishell, "HOME")) != 0)
			ft_printf("bash: cd: HOME not set\n");
		else
			ft_swap_pwd(minishell, pwd);
	}
	else if (ft_strcmp(ast->value, "~") == 0)
	{
		chdir("/home/pabromer");
		ft_swap_pwd(minishell, pwd);
	}
}

static void ft_abs_dir(t_minishell *minishell, t_ast *ast, char *pwd)
{
	char	*join;

	join = ft_strjoin("/home/pabromer",ft_strchr(ast->value, '/'));
	if (chdir(join) != 0)
	{
		minishell->exit = 1;
		ft_printf("bash: cd: %s: No such file or directory\n", ast->value);
	}
	else
		ft_swap_pwd(minishell, pwd);
	free(join);
}

static void ft_cd_oldpwd(t_minishell *minishell, char *pwd)
{
	if (!ft_find_dir(minishell, "OLDPWD"))
		ft_printf("bash: cd: OLDPWD not set\n");
	else
	{
		chdir(ft_find_dir(minishell, "OLDPWD"));
		ft_printf("%s\n", ft_find_dir(minishell, "OLDPWD"));
		ft_swap_pwd(minishell, pwd);
	}
}

static void	ft_try_cd(t_minishell *minishell, t_ast *ast, int i, char *pwd)
{
	if (i > 2)
	{
		minishell->exit = 1;
		ft_printf("bash: cd: too many arguments\n");
	}
	else if (ft_strcmp(ast->value, "-") == 0)
		ft_cd_oldpwd(minishell, pwd);
	else if (ast->value[0] == '~' && ast->value[1] == '/')
		ft_abs_dir(minishell, ast, pwd);
	else
	{
		if (chdir(ast->value) != 0)
		{
			minishell->exit = 1;
			ft_printf("bash: cd: %s: No such file or directory\n", ast->value);
		}
		else
			ft_swap_pwd(minishell, pwd);
	}
}

void	ft_cd(t_minishell *minishell, t_ast *ast)
{
	int		i;
	t_ast	*temp;
	char	*pwd;
	char	cwd[1024];
	
	i = 1;
	pwd = NULL;
	temp = ast;
	while (ast->left)
	{
		i++;
		ast = ast->left;
	}
	minishell->exit = 0;
	pwd = getcwd(cwd, sizeof(cwd));
	if (i == 1 || ft_strcmp(ast->value, "~") == 0)
	{
		ft_cd_only(minishell, ast, i, pwd);
		ast = temp;
		return ;
	}
	ft_try_cd(minishell, ast, i, pwd);
	ast = temp;
}
