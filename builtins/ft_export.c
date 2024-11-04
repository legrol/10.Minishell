/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:37:36 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/04 10:55:04 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*static t_envp	*new_node_envp(char *key, char *value)
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
	new_node->next = NULL;	
	return (new_node);
}

static int ft_count_lines(t_minishell *minishell)
{
	t_envp *temp;
	int		i;

	i = 0;
	temp = minishell->list_envp;
	while(minishell->list_envp)
	{
		i++;
		minishell->list_envp = minishell->list_envp->next;
	}
	minishell->list_envp = temp;
	return (i);
}

static char **ft_copy_env(t_minishell *minishell)
{
	t_envp *temp;
	char	**cpy;
	int i;
	cpy = (char **)ft_calloc((ft_count_lines(minishell)+1),sizeof(char*));
	if (!cpy)
		return (NULL);
	temp = minishell->list_envp;
	i = 0;
	while(minishell->list_envp->next)
	{
		cpy[i] = ft_strdup(minishell->list_envp->key);
		i++;
		minishell->list_envp = minishell->list_envp->next;
	}
	cpy[i] = NULL;
	minishell->list_envp = temp;
	return (cpy);
}
static char **ft_sort_print(t_minishell *minishell)
{
	char	**cpy;
	int		i;
	char	*temp;

	cpy = ft_copy_env(minishell);
	i = 0;
	while(cpy[i+1])
	{
		if (ft_strcmp(cpy[i], cpy[i+1]) > 0)
		{
			temp = cpy[i+1];
			cpy[i+1] = cpy[i];
			cpy[i] = temp;
			i = -1;
		}
		i++;
	}
	return (cpy);
}
static void ft_export_only(t_minishell *minishell)
{
	char	**cpy;
	int		i;
	t_envp	*temp;
	
	cpy = ft_sort_print(minishell);
	temp = minishell->list_envp;
	i = 0;
	while(cpy[i])
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

static int ft_find_key(t_minishell *minishell, char *key, char *value)
{
	t_envp *temp;

	temp = minishell->list_envp;
	while(minishell->list_envp)
	{
		if(ft_strcmp(key, minishell->list_envp->key) == 0)
		{
			if (minishell->list_envp->value)
				free(minishell->list_envp->value);
			if (!value)
				minishell->list_envp->value = NULL;
			else
				minishell->list_envp->value = ft_strdup(value);
			minishell->list_envp = temp;
			return (0);
		}
		minishell->list_envp = minishell->list_envp->next;
	}
	minishell->list_envp = temp;
	return (-1);
}

static int ft_arg_checker(t_ast *ast, t_minishell *minishell)
{
	int i;
	t_ast *temp2;
	int f;

	i = 0;
	f = 0;
	temp2 = ast;
	while (ast)
	{
		if (ft_isalpha(ast->value[0]) == 0)
		{
			minishell->exit = 1;
			ft_printf("minishell: export: \'%s\': not a valid identifier\n",\
			ast->value);
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

static char **ft_init_keyvalue(void)
{
	char	**key_value;

	key_value = (char **)malloc(2*sizeof(char*));
	if (!key_value)
		return NULL;
	key_value[0] = NULL;
	key_value[1] = NULL;
	return (key_value);
}

static void ft_fill_keyvalue(char	**key_value, t_ast *ast)
{
	if (ft_strchr(ast->value, '='))
	{
		key_value[0] = ft_substr(ast->value,0,ft_strlen(ast->value)-ft_strlen(ft_strchr(ast->value, '=')));
		key_value[1] = ft_strdup(ft_strchr_exp(ast->value, '='));
	}
	else
	{
		key_value[0] = ft_strdup(ast->value);
		key_value[1] = NULL;
	}
}*/

static void	ft_insert_node(t_minishell *minishell, t_ast *ast)
{
	char	**key_value;
	t_envp 	*temp;
	t_envp 	*new_node;

	key_value = ft_init_keyvalue();
	while(ast)
	{
		ft_fill_keyvalue(key_value, ast);
		if (ft_find_key(minishell, key_value[0], key_value[1]) == -1)
		{
			new_node = new_node_envp(key_value[0], key_value[1]);
			temp = minishell->list_envp;
			while(ft_strcmp(minishell->list_envp->key, "XDG_GREETER_DATA_DIR") != 0 && minishell->list_envp->next->next)
				minishell->list_envp = minishell->list_envp->next;
			new_node->next = minishell->list_envp->next;
			minishell->list_envp->next = new_node;
			minishell->list_envp = temp;
		}
		ast = ast->left;
		free(key_value[0]);
		if (key_value[1])
			free(key_value[1]);
	}
	free(key_value);
}

void ft_export(t_minishell *minishell, t_ast *ast)
{
	int i;
	t_ast *temp2;

	minishell->exit = 0;
	i = ft_arg_checker(ast, minishell);
	if (i == -1 || i == 1)
		return ;
	temp2 = ast;
	ast = ast->left;
	ft_insert_node(minishell, ast);
	ast = temp2;
}

