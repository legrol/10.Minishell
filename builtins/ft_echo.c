/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:36:47 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/28 17:35:48 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_echo" implements the behavior of the `echo` command in 
 * the minishell program. It processes the arguments provided in the `ast` 
 * structure, evaluates the presence of the `-n` flag, and prints the 
 * arguments accordingly.
 * 
 * - If the `-n` flag is present, it suppresses the trailing newline.
 * - If no arguments are provided, it prints a newline by default.
 * - The function also handles special cases for argument parsing and ensures 
 *   that memory is freed after execution.
 * 
 * @param t_minishell *minishell	A pointer to the `t_minishell` structure 
 *									representing the state of the shell.
 * 
 * @param t_ast *ast				A pointer to the `t_ast` structure 
 * 									containing 
 *									the command and its arguments in a linked 
 *									tree format.
 * 
 * @return void						This function does not return a value.
 * 
 * The function "ft_echo_init" processes the `ast` tree to determine if the 
 * `-n` flag (used to suppress the newline in the `echo` command) is present.
 * It iterates through the linked nodes in the `ast` tree and evaluates the 
 * command's structure.
 * 
 * - Returns `-1` if no additional arguments are provided.
 * - Returns `1` if the `-n` flag is detected.
 * - Returns `2` if there are additional arguments that start with `-`.
 * 
 * @param t_ast *ast	A pointer to the `t_ast` structure representing the 
 *						command and its arguments in the Abstract Syntax Tree.
 * 
 * @return int			A status code indicating the presence and type of 
 *						flags/arguments in the `ast` structure.
 * 
 * The function "ft_trim_ast" trims the character `n` from the string stored 
 * in the `value` field of the given `ast` node if the string starts with a 
 * dash (`-`). If it does not start with a dash, the function simply duplicates
 * the string without modifications.
 * 
 * - This function is primarily used in the context of parsing and handling
 *   options (e.g., `-n`) in the `ft_echo` command.
 * 
 * @param t_ast *ast	A pointer to the `t_ast` structure containing the 
 *						string (`ast->value`) to be processed.
 * 
 * @return char*		A newly allocated string containing the processed 
 *						value from the `ast` node. The caller is responsible 
 *						for freeing this string.
 * 
 */

static char	*ft_trim_ast(t_ast *ast)
{
	char	*trim;

	if (ast->value[0] == '-')
		trim = ft_strtrim(ast->value, "n");
	else
		trim = ft_strdup(ast->value);
	return (trim);
}

static int	ft_echo_init(t_ast *ast)
{
	int		i;
	t_ast	*temp;
	int		f;
	char	*trim;

	f = 0;
	i = 0;
	temp = ast;
	while (ast)
	{
		trim = ft_trim_ast(ast);
		if (i >= 1 && ft_strcmp(trim, "-") == 0 && f == 0)
			f = 1;
		if (i >= 1 && ft_strcmp(trim, "-") == 0)
			f = 2;
		i++;
		ast = ast->left;
		free(trim);
	}
	ast = temp;
	if (i == 1)
		return (-1 + (0 * printf("\n")));
	else if (f == 1)
		return (-1 + (0 * printf("")));
	return (f);
}

void	ft_echo(t_minishell *minishell, t_ast *ast)
{
	t_ast	*temp;
	int		f;

	f = 0;
	temp = ast;
	f = ft_echo_init(ast);
	if (f == -1)
		return ;
	ast = ast->left;
	while (ast && ft_strcmp(ast->value, "-n") == 0)
		ast = ast->left;
	while (ast)
	{
		ft_printf("%s", ast->value);
		if (ast->left)
			ft_printf(" ", ast->value);
		ast = ast->left;
	}
	if (f == 0)
		ft_printf("\n");
	minishell->exit = 0;
	ast = temp;
}
