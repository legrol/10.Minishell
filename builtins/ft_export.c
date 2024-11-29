/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:37:36 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/29 15:20:59 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_export" processes the export command by validating and 
 * adding new environment variables or printing them.
 *
 * - Calls `ft_arg_checker` to validate the arguments in the AST.
 * - If only one argument is present, prints the environment variables in a 
 *   sorted order.
 * - If there are multiple valid arguments, adds them to the environment list 
 *   using `ft_insert_node`.
 *
 * @param t_minishell *minishell 	A pointer to the minishell structure for 
 * 									managing the environment list and exit 
 * 									status.
 * @param t_ast *ast             	A pointer to the abstract syntax tree node 
 * 									containing the arguments for the export 
 * 									command.
 * 
 * The function "ft_arg_checker" validates arguments in the AST to ensure they 
 * are valid identifiers and determines the operation type for export.
 *
 * - Validates the first character of each argument to ensure it is 
 *   alphanumeric 
 *   or an underscore.
 * - Calls `ft_export_only` if there is only one argument and no errors.
 * - Sets the exit status to 1 and returns -1 if invalid arguments are found.
 *
 * @param t_ast *ast				A pointer to the abstract syntax tree 
 * 									node containing arguments to validate.
 * @param t_minishell *minishell 	A pointer to the minishell structure for 
 * 									managing the exit status.
 *
 * @return int 						The number of arguments if valid, or -1 if 
 * 									invalid arguments are found.
 * 
 * The function "ft_insert_node" processes and inserts new environment variable 
 * nodes into the environment list based on the AST values.
 *
 * - Iterates through the AST, splitting its value into key-value pairs.
 * - Validates the keys using `ft_ast_checker`.
 * - Adds new nodes to the environment list using `ft_prueba` if the key is 
 *   valid.
 * - Frees dynamically allocated memory after processing each node.
 *
 * @param t_minishell *minishell 	A pointer to the minishell structure 
 * 									containing the environment list.
 * @param t_ast *ast             	A pointer to the abstract syntax tree node
 *									containing values to process.
 * 
 * The function "ft_export_only" prints the environment variables in a sorted 
 * order, formatted as `declare -x` statements.
 *
 * - Creates a sorted copy of the environment variable keys using 
 *   `ft_sort_print`.
 * - Iterates through the sorted keys, matches them with their corresponding 
 *   values in the environment list, and prints them in the correct format.
 * - Frees the allocated memory for the sorted copy.
 *
 * @param t_minishell *minishell 	A pointer to the minishell structure 
 * 									containing the environment list.
 * 
 * The function "ft_init_keyvalue" initializes a dynamically allocated array 
 * for storing a key-value pair with two elements.
 *
 * - Allocates memory for a `char**` array with space for two elements.
 * - Initializes both elements (`key_value[0]` and `key_value[1]`) to `NULL`.
 *
 * @return char** 					A pointer to the allocated and initialized
 * 									key-value array, or `NULL` if memory 
 * 									allocation fails.
 * 
 */

static char	**ft_init_keyvalue(void)
{
	char	**key_value;

	key_value = (char **)malloc(2 * sizeof(char *));
	if (!key_value)
		return (NULL);
	key_value[0] = NULL;
	key_value[1] = NULL;
	return (key_value);
}

static void	ft_export_only(t_minishell *minishell)
{
	char	**cpy;
	int		i;
	t_envp	*temp;

	cpy = ft_sort_print(minishell);
	temp = minishell->list_envp;
	i = 0;
	while (cpy[i])
	{
		while (ft_strcmp(cpy[i], minishell->list_envp->key) != 0)
			minishell->list_envp = minishell->list_envp->next;
		if (ft_strcmp(cpy[i], "ZDOTDIR") == 0 || ft_strcmp(cpy[i], "_") == 0)
			;
		else if (minishell->list_envp->value)
			ft_printf("declare -x %s=\"%s\"\n", minishell->list_envp->key, \
			minishell->list_envp->value);
		else
			ft_printf("declare -x %s\n", minishell->list_envp->key);
		free(cpy[i]);
		minishell->list_envp = temp;
		i++;
	}
	free(cpy[i]);
	minishell->list_envp = temp;
	free(cpy);
}

static void	ft_insert_node(t_minishell *minishell, t_ast *ast)
{
	char	**key_value;
	int		check;

	key_value = ft_init_keyvalue();
	while (ast)
	{
		ft_fill_keyvalue(key_value, ast);
		check = ft_ast_checker(key_value[0], ast, minishell);
		while (check == -1 && ast->left)
		{
			free(key_value[0]);
			if (key_value[1])
				free(key_value[1]);
			ast = ast->left;
			ft_fill_keyvalue(key_value, ast);
			check = ft_ast_checker(key_value[0], ast, minishell);
		}
		ft_insert_node_in_env(minishell, ast, key_value, check);
		ast = ast->left;
		free(key_value[0]);
		if (key_value[1])
			free(key_value[1]);
	}
	free(key_value);
}

static int	ft_arg_checker(t_ast *ast, t_minishell *minishell)
{
	int		i;
	t_ast	*temp2;
	int		f;

	i = 0;
	f = 0;
	temp2 = ast;
	while (ast)
	{
		if (ft_isalnum(ast->value[0]) == 0 && ast->value[0] != '_')
		{
			minishell->exit = 1;
			f = -1;
		}
		i++;
		ast = ast->left;
	}
	if (i == 1)
		ft_export_only(minishell);
	if (f == -1)
		return (f);
	ast = temp2;
	return (i);
}

void	ft_export(t_minishell *minishell, t_ast *ast)
{
	int		i;
	t_ast	*temp2;

	minishell->exit = 0;
	i = ft_arg_checker(ast, minishell);
	if (i == 1)
		return ;
	temp2 = ast;
	ast = ast->left;
	ft_insert_node(minishell, ast);
	ast = temp2;
}
