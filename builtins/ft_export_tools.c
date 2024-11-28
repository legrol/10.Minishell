/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-28 11:01:24 by rdel-olm          #+#    #+#             */
/*   Updated: 2024-11-28 11:01:24 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_fill_keyvalue" splits a string from the AST into a key and
 * value pair and stores them in the provided `key_value` array.
 *
 * - If the string contains an '=', splits it into the key and value.
 * - If no '=', assigns the entire string to the key and sets the value to 
 *   NULL.
 *
 * @param char **key_value 			An array to store the key and value 
 * 									strings.
 * @param t_ast *ast       			The abstract syntax tree node containing 
 * 									the string to split.
 * 
 * The function "ft_ast_checker" validates a key from the AST based on specific
 * naming rules and returns an indicator of its validity.
 *
 * - Checks if the key ends with a '+' and adjusts the check value accordingly.
 * - Verifies that the key contains only valid characters (letters, digits, 
 *   '_').
 * - If the key is invalid, prints an error message and sets the exit status.
 *
 * @param char *key        			The key to validate.
 * @param t_ast *ast       			The abstract syntax tree node containing 
 * 									the key.
 * @param t_minishell *minishell 	A pointer to the minishell structure for 
 * 									managing the exit status.
 *
 * @return int 2 					if the key is valid and ends with a '+', 
 * 									-1 if invalid, or 0 otherwise.
 * 
 * The function "ft_prueba" handles adding or updating environment variables
 * in the minishell environment list based on specific conditions.
 *
 * - If the AST value contains an '=' or the key does not exist, attempts to
 *   add or update the variable in the environment list.
 * - Uses `new_node_envp` to create a new node if the key does not exist.
 * - Inserts the new node into the correct position in the environment list.
 *
 * @param t_minishell *minishell 	A pointer to the minishell structure 
 * 									containing the environment list.
 * @param t_ast *ast             	The abstract syntax tree node containing 
 * 									the value to process.
 * @param char **key_value       	An array containing the key and value 
 * 									strings.
 * @param int check              	Indicates the operation type for 
 * 									`ft_find_key`.
 * 
 * The function "ft_sort_print" creates a sorted copy of the environment 
 * variable keys and returns it.
 *
 * - Copies the environment keys into a new dynamically allocated array.
 * - Sorts the array in lexicographical order using a bubble sort algorithm.
 * - Returns the sorted array for further use.
 *
 * @param t_minishell *minishell 	A pointer to the minishell structure 
 * 									containing the environment list.
 *
 * @return char** A dynamically allocated array of sorted environment keys.
 * 
 * The function "new_node_envp" creates a new node for the environment list.
 *
 * - Allocates memory for a new `t_envp` node.
 * - Initializes the `key` with the provided string, duplicating it.
 * - Sets the `value` to a duplicate of the provided string or `NULL` if no 
 *   value is given.
 * - Sets the `next` pointer to `NULL`.
 *
 * @param char *key   				The key for the environment variable.
 * @param char *value 				The value for the environment variable 
 * 									(optional, can be NULL).
 *
 * @return t_envp* 					A pointer to the newly created node or 
 * 									`NULL` if memory allocation fails.
 * 
 */

static t_envp	*new_node_envp(char *key, char *value)
{
	t_envp	*new_node;

	new_node = (t_envp *)malloc(sizeof(t_envp));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (!value)
		new_node->value = NULL;
	else
		new_node->value = ft_strdup(value);
	new_node->next = (NULL);
	return (new_node);
}

char	**ft_sort_print(t_minishell *minishell)
{
	char	**cpy;
	int		i;
	char	*temp;

	cpy = ft_copy_env(minishell);
	i = 0;
	while (cpy[i + 1])
	{
		if (ft_strcmp(cpy[i], cpy[i + 1]) > 0)
		{
			temp = cpy[i + 1];
			cpy[i + 1] = cpy[i];
			cpy[i] = temp;
			i = -1;
		}
		i++;
	}
	return (cpy);
}

void	ft_prueba(t_minishell *minishell, t_ast *ast, \
char **key_value, int check)
{
	t_envp	*temp;
	t_envp	*new_node;

	if (ft_strchr(ast->value, '=') || ft_find_only_key(minishell, \
	key_value[0]) != 0)
	{
		if (ft_find_key(minishell, key_value, check) == -1)
		{
			new_node = new_node_envp(key_value[0], key_value[1]);
			temp = minishell->list_envp;
			while (ft_strcmp(minishell->list_envp->key, \
			"XDG_GREETER_DATA_DIR") != 0 && \
			minishell->list_envp->next->next)
				minishell->list_envp = minishell->list_envp->next;
			new_node->next = minishell->list_envp->next;
			minishell->list_envp->next = new_node;
			minishell->list_envp = temp;
		}
	}
}

int	ft_ast_checker(char *key, t_ast *ast, t_minishell *minishell)
{
	int	i;
	int	j;
	int	l;

	i = 0;
	j = 0;
	l = ft_strlen(key) - 1;
	if (key[l] == '+')
		i = 2;
	while (j < l)
	{
		if (ft_isalpha(key[j]) == 0 && key[j] != '_')
			i = -1;
		j++;
	}
	if (ft_isalpha(key[j]) == 0 && key[j] != '_' && key[j] != '+')
		i = -1;
	if (i == -1)
	{
		minishell->exit = 0;
		ft_printf("minishell: export: \'%s\': not a valid identifier\n", \
		ast->value);
	}
	ft_printf("i: %i\n", i);
	return (i);
}

void	ft_fill_keyvalue(char	**key_value, t_ast *ast)
{
	if (ft_strchr(ast->value, '='))
	{
		key_value[0] = ft_substr(ast->value, 0, \
		ft_strlen(ast->value) - ft_strlen(ft_strchr(ast->value, '=')));
		key_value[1] = ft_strdup(ft_strchr_exp(ast->value, '='));
	}
	else
	{
		key_value[0] = ft_strdup(ast->value);
		key_value[1] = NULL;
	}
}
