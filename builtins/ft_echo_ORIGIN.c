/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:36:47 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/06 10:09:50 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * 
 * FALTA liberar el split
*/

static char ft_find_special_char(char *s)
{
	int i;

	i=0;
	while(s[i])
	{
		if (ft_isalnum(s[i]) == 0 && s[i] != '_')
			return (s[i]);
		i++;
	}
	return ('\0');
}

static void	ft_expand_echo(t_minishell *minishell, t_ast *ast)
{
	char	**split;
	int		i;
	char	a;
	char	*b;

	i = 0;
	split = ft_split_m(ast->value, '$');
	b = NULL;
	while(split[i])
	{
		a = ft_find_special_char(split[i]);
		if(split[i][0] == '?')
			ft_printf("%i%s", minishell->exit, ft_strchr_exp(split[i], '?'));
		else if(a && ft_strchr(split[i], a))
		{
			b = ft_substr(split[i], 0, ft_strlen(split[i]) - ft_strlen(ft_strchr(split[i], a)));
			ft_printf("%s%s",ft_find_dir(minishell, b) ,ft_strchr(split[i], a));
			free(b);
		}
		else if (ft_find_dir(minishell, split[i]))
			ft_printf("%s", ft_find_dir(minishell, split[i]));
		else 
			ft_printf("%s", split[i]);
		free(split[i]);
		i++;
	}
	ft_printf(" ");
	free(split);
}

static char *ft_trim_ast(t_ast *ast)
{
	char *trim;

	if (ast->value[0] == '-')
		trim = ft_strtrim(ast->value, "n");
	else
		trim = ft_strdup(ast->value);
	return (trim);
}

static int ft_echo_init(t_ast *ast)
{
	int i;
	t_ast *temp;
	int f;
	char *trim;

	f = 0;
	i = 0;
	temp = ast;
	while (ast)
	{
		trim = ft_trim_ast(ast);
		if (i >= 1 && ft_strcmp(trim, "-") == 0 && f == 0)
			f = 1;
		if (i >=1 && ft_strcmp(trim, "-") == 0)
			f = 2;
		i++;
		ast = ast->left;
		free(trim);
	}
	ast = temp;
	if (i == 1)
		return (-1+(0*printf("\n")));
	else if (f == 1)
		return (-1+(0*printf("")));
	return (f);
}

void	ft_echo(t_minishell *minishell, t_ast *ast)
{
	t_ast *temp;
	int f;
	char	*trim;

	f = 0;
	temp = ast;
	f = ft_echo_init(ast);
	if (f == -1)
		return;
	ast = ast->left;
	if (f == 2)
	while(ast && ft_strcmp(ast->value,"-n") == 0)
		ast = ast->left;
	while(ast)
	{
		trim = ft_strtrim(ast->value, "'");
		if (ft_strchr(ast->value, '$') && ft_strlen(ast->value) == ft_strlen(trim))
			ft_expand_echo(minishell, ast);
		else
			ft_printf("%s ", trim);
		free(trim);
		ast = ast->left;
	}
	if (f == 0)
		ft_printf("\n");
	minishell->exit = 0;
	ast = temp;
}
