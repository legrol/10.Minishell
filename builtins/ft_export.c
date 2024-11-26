/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:37:36 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/27 17:42:58 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static int	ft_count_lines(t_minishell *minishell)
{
	t_envp	*temp;
	int		i;

	i = 0;
	temp = minishell->list_envp;
	while (minishell->list_envp)
	{
		i++;
		minishell->list_envp = minishell->list_envp->next;
	}
	minishell->list_envp = temp;
	return (i);
}

static char	**ft_copy_env(t_minishell *minishell)
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

static char	**ft_sort_print(t_minishell *minishell)
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

static int	ft_find_key(t_minishell *minishell, char **key_value, int check)
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

static int	ft_find_only_key(t_minishell *minishell, char *key)
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

static void	ft_fill_keyvalue(char	**key_value, t_ast *ast)
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

static int	ft_ast_checker(char *key, t_ast *ast, t_minishell *minishell)
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

static void	ft_prueba(t_minishell *minishell, t_ast *ast, \
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
		ft_prueba(minishell, ast, key_value, check);
		ast = ast->left;
		free(key_value[0]);
		if (key_value[1])
			free(key_value[1]);
	}
	free(key_value);
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
