/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:45:58 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/10/15 23:27:32 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_init_list_envp" initializes a linked list of environment 
 * variables from the `envp` array. It creates a linked list of `t_envp` 
 * nodes, where each node contains a key-value pair representing an environment 
 * variable.
 * 
 * @param char **envp		String array containing the system environment 
 * 							variables. These are needed for initializing the 
 * 							`t_minishell` structure and managing the shell 
 * 							environment.
 * 
 * The function "create_node_and_add" Creates a new node with the environment 
 * variable from envp.
 * 
 * @param t_envp *head		Pointer to the last node in the current linked 
 * 							list.
 * @param char *envp		The full environment variable string (e.g., 
 * 							"PATH=/usr/bin"). 
 * 
 * The function "split_envp" splits a single environment variable string into 
 * a key-value pair. The string is split at the first occurrence of the '=' 
 * character. If there is no '=', the entire string is considered the key, 
 * and the value is NULL.
 * 
 * @param const char *envp	The environment variable string to be split.
 * @param char **key		Pointer to store the extracted key.
 * @param char **value		Pointer to store the extracted value. If there 
 * 							is no '=' in the input string, this will be set 
 * 							to NULL.
 * 
 * The function "new_node_envp" creates a new `t_envp` node with the provided 
 * key and value. The function allocates memory for the node and copies the 
 * key and value.
 * 
 * @param char *key			The key for the environment variable (before 
 * 							the '=').
 * @param char *value		The value for the environment variable (after 
 * 							the '='). Can be NULL if there is no value.
 * 
 */

static t_envp	*new_node_envp(char *key, char *value)
{
	t_envp	*new_node;

	new_node = (t_envp *)malloc(sizeof(t_envp));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}

static void	split_envp(const char *envp, char **key, char **value)
{
	int		key_len;
	char	*find_equal;

	find_equal = ft_strchr(envp, '=');
	if (find_equal)
	{
		key_len = find_equal - envp;
		*key = ft_substr(envp, 0, key_len);
		*value = ft_strdup(find_equal + 1);
	}
	else
	{
		*key = ft_strdup(envp);
		*value = NULL;
	}
}

t_envp	*create_node_and_add(t_envp *head, char *envp)
{
	char	*key;
	char	*value;
	t_envp	*new_node;

	split_envp(envp, &key, &value);
	new_node = new_node_envp(key, value);
	free(key);
	if (value)
		free(value);
	if (!new_node)
		return (NULL);
	if (!head)
		return (new_node);
	return (head->next = new_node);
}

t_envp	*ft_init_list_envp(char **envp)
{
	int		i;
	t_envp	*head;
	t_envp	*current;

	i = 0;
	head = NULL;
	current = NULL;
	while (envp[i])
	{
		current = create_node_and_add(current, envp[i]);
		if (!current)
			return (NULL);
		if (!head)
			head = current;
		i++;
	}
	return (head);
}
