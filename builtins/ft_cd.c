/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:35:33 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/08 13:36:32 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_cd" implements the behavior of the `cd` command in the 
 * minishell. It parses arguments, determines the appropriate behavior for 
 * special cases (e.g., `cd -`, `cd ~`), and updates the working directory 
 * (`PWD`) and previous directory (`OLDPWD`).
 * 
 * - Handles multiple arguments and prints an error for excessive arguments.
 * - Updates the prompt after a successful directory change.
 * - Supports relative and absolute paths as well as environment-based paths.
 * 
 * @param t_minishell *minishell	A pointer to the shell's state structure.
 * 
 * @param t_ast *ast				A pointer to the `t_ast` structure 
 * 									containing the target directory or options.
 * 
 * The function "ft_try_cd" attempts to execute the `cd` command based on the 
 * provided arguments. It handles special cases like too many arguments, 
 * `cd -`, paths starting with `~`, and general directory changes.
 * 
 * - If the directory does not exist, it prints an error message.
 * - Updates the `PWD` and `OLDPWD` variables on success.
 * 
 * @param t_minishell *minishell	A pointer to the shell's state structure.
 * 
 * @param t_ast *ast				A pointer to the `t_ast` structure 
 * 									containing the target directory or options.
 * 
 * @param int i						The number of arguments provided to the 
 * 									`cd` command.
 * 
 * @param char *pwd					A string representing the previous working 
 *									directory (`OLDPWD`).
 * 
 * The function "ft_cd_oldpwd" handles the `cd -` command, which changes 
 * the working directory to the value stored in `OLDPWD`.
 * 
 * - Prints an error message if `OLDPWD` is not set.
 * - On success, updates the working directory and prints the new path.
 * 
 * @param t_minishell *minishell	A pointer to the shell's state structure.
 * 
 * @param char *pwd					A string representing the previous working
 *									directory (`OLDPWD`).
 * 
 * The function "ft_abs_dir" handles absolute directory changes when the `cd` 
 * command contains a path that starts with `~` followed by `/`. It resolves 
 * the absolute path by appending the specified path to the user's home 
 * directory and attempts to change to the resulting directory.
 * 
 * - Prints an error message if the directory does not exist.
 * - Updates the `PWD` and `OLDPWD` variables on success.
 * 
 * @param t_minishell *minishell	A pointer to the shell's state structure.
 * 
 * @param t_ast *ast				A pointer to the `t_ast` structure 
 * 									containing the target directory path.
 * 
 * @param char *pwd					A string representing the previous working 
 *									directory (`OLDPWD`).
 * 
 * The function "ft_cd_only" handles the `cd` command when no arguments are 
 * provided, or the argument is `~`. It changes the directory to `HOME` or a 
 * fallback home directory and updates the `PWD` and `OLDPWD` variables.
 * 
 * - If `HOME` is not set in the environment, it prints an error message.
 * - Handles tilde (`~`) as a shorthand for the home directory.
 * 
 * @param t_minishell *minishell	A pointer to the shell's state structure, 
 *									which contains environment variables.
 * 
 * @param t_ast *ast				A pointer to the `t_ast` structure 
 * 									containing the command and its arguments.
 * 
 * @param int i						The number of arguments provided to the 
 * 									`cd` command.
 * 
 * @param char *pwd					A string representing the previous working 
 *									directory (`OLDPWD`).
 * 
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
 *									directory (`OLDPWD`).
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
		if (ft_find_dir(minishell, "HOME") == NULL)
			ft_printf("bash: cd: HOME not set\n");
		else
		{
			chdir(ft_find_dir(minishell, "HOME"));
			ft_swap_pwd(minishell, pwd);
		}
	}
	else if (ft_strcmp(ast->value, "~") == 0)
	{
		chdir("/home/pabromer");
		ft_swap_pwd(minishell, pwd);
	}
}

static void	ft_abs_dir(t_minishell *minishell, t_ast *ast, char *pwd)
{
	char	*join;

	join = ft_strjoin("/home/pabromer", ft_strchr(ast->value, '/'));
	if (chdir(join) != 0)
	{
		minishell->exit = 1;
		ft_printf("bash: cd: %s: No such file or directory\n", ast->value);
	}
	else
		ft_swap_pwd(minishell, pwd);
	free(join);
}

static void	ft_cd_oldpwd(t_minishell *minishell, char *pwd)
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
