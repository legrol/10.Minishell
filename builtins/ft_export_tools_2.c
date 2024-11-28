/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_tools_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-28 11:03:54 by rdel-olm          #+#    #+#             */
/*   Updated: 2024-11-28 11:03:54 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_find_only_key" searches for a key in the minishell 
 * environment list without modifying its value.
 *
 * - Iterates through the environment list to find the key.
 * - Returns 0 if the key is found.
 * - Returns -1 if the key does not exist.
 *
 * @param t_minishell *minishell A pointer to the minishell structure 
 * 								 containing 
 *                               the environment list.
 * @param char *key              The key to search for in the environment list.
 *
 * @return int 0 if the key is found, or -1 if the key does not exist.
 * 
 * The function "ft_find_key" searches for a key in the minishell environment
 * list and updates its value if found.
 *
 * - If `check == 2`, trims the key before searching.
 * - If the key exists, updates its value using "ft_find_key_2".
 * - Returns 0 if the key is found and updated.
 * - Returns -1 if the key does not exist.
 *
 * @param t_minishell *minishell A pointer to the minishell structure 
 * 								 containing 
 *                               the environment list.
 * @param char **key_value       An array where `key_value[0]` is the key to be 
 *                               searched and `key_value[1]` is the new value.
 * @param int check              Indicates the operation type:
 *                               - 2 for trimming and appending.
 *                               - Other values for direct replacement.
 *
 * @return int 0 				if the key is found, or -1 if the key does not
 * 								exist.
 * 
 * The function "ft_copy_env" creates a copy of the current environment 
 * variables from the minishell environment list into a dynamically allocated
 * array.
 *
 * - Iterates through `minishell->list_envp` and duplicates each key.
 * - Returns a NULL-terminated array containing the keys from the environment.
 *
 * @param t_minishell *minishell A pointer to the minishell structure 
 * 								 containing 
 *                               the environment list.
 *
 * @return char** 				 A dynamically allocated array of strings 
 * 								 containing the keys from the environment, or
 * 								 `NULL` if allocation fails.
 * 
 * The function "ft_find_key_2" updates or appends a value to an existing key
 * in the minishell environment list, based on the `check` parameter.
 *
 * - If `check == 2`, appends `key_value[1]` to the existing value of the key.
 * - Otherwise, replaces the current value with `key_value[1]` or sets it to 
 *   `NULL` if `key_value[1]` is missing.
 *
 * @param t_minishell *minishell A pointer to the minishell structure 
 * 								 containing 
 *                               the environment list.
 * @param char **key_value       An array where `key_value[0]` is the key and 
 *                               `key_value[1]` is the value to be updated.
 * @param int check              Indicates the operation type:
 *                               - 2 for appending.
 *                               - Other values for replacement.
 * 
 * The function "ft_trim_key" trims any '+' characters from the provided key
 * in the `key_value` array and updates the key with the trimmed result.
 *
 * - Uses `ft_strtrim` to remove '+' characters from `key_value[0]`.
 * - Frees the old key and replaces it with the new trimmed key.
 *
 * @param char **key_value 		An array where `key_value[0]` is the key to be
 *                         		trimmed and updated.
 * 
 */

static void	ft_trim_key(char **key_value)
{
	char	*temp;

	temp = ft_strtrim(key_value[0], "+");
	free(key_value[0]);
	key_value[0] = ft_strdup(temp);
	free(temp);
}

static void	ft_find_key_2(t_minishell *minishell, char **key_value, int check)
{
	char	*temp_value;

	if (minishell->list_envp->value && check == 2 && key_value[1])
	{
		temp_value = ft_strdup(minishell->list_envp->value);
		free(minishell->list_envp->value);
		minishell->list_envp->value = ft_strjoin(temp_value, key_value[1]);
		free(temp_value);
	}
	else if ((minishell->list_envp->value || key_value[1]) && check != 2)
	{
		if (minishell->list_envp->value)
			free(minishell->list_envp->value);
		if (!key_value[1])
			minishell->list_envp->value = NULL;
		else
			minishell->list_envp->value = ft_strdup(key_value[1]);
	}
}

char	**ft_copy_env(t_minishell *minishell)
{
	t_envp	*temp;
	char	**cpy;
	int		i;

	cpy = (char **)ft_calloc((ft_count_lines(minishell) + 1), sizeof(char *));
	if (!cpy)
		return (NULL);
	temp = minishell->list_envp;
	i = 0;
	while (minishell->list_envp->next)
	{
		cpy[i] = ft_strdup(minishell->list_envp->key);
		i++;
		minishell->list_envp = minishell->list_envp->next;
	}
	cpy[i] = NULL;
	minishell->list_envp = temp;
	return (cpy);
}

int	ft_find_key(t_minishell *minishell, char **key_value, int check)
{
	t_envp	*temp;

	temp = minishell->list_envp;
	if (check == 2)
		ft_trim_key(key_value);
	while (minishell->list_envp)
	{
		if (ft_strcmp(key_value[0], minishell->list_envp->key) == 0)
		{
			ft_find_key_2(minishell, key_value, check);
			minishell->list_envp = temp;
			return (0);
		}
		minishell->list_envp = minishell->list_envp->next;
	}
	minishell->list_envp = temp;
	return (-1);
}

int	ft_find_only_key(t_minishell *minishell, char *key)
{
	t_envp	*temp;

	temp = minishell->list_envp;
	while (minishell->list_envp)
	{
		if (ft_strcmp(key, minishell->list_envp->key) == 0)
		{
			minishell->list_envp = temp;
			return (0);
		}
		minishell->list_envp = minishell->list_envp->next;
	}
	minishell->list_envp = temp;
	return (-1);
}
