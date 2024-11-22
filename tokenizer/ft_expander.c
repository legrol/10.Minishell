/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/11/22 22:22:13 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char ft_find_special_char(char *s)
{
	int i;
	if (!s)
		return ('\0');
	i=0;
	while(s[i])
	{
		if (ft_isalnum(s[i]) == 0 && s[i] != '_')
			return (s[i]);
		i++;
	}
	return ('\0');
}

static char *ft_change_token(char *dup, char *temp, char *sp)
{
	char *t;
	char *join;

	if (temp && dup)
		join = ft_strjoin(dup, temp);
	else if (dup)
		join = ft_strdup(dup);
	else 
		join = ft_strdup(temp);
	if (dup)
		free(dup);
	dup = ft_strdup(join);
	free(join);
	join = ft_strjoin(dup, sp);
	t = ft_strdup(join);
	if (temp)
		free(temp);
	free(join);
	free(sp);
	free(dup);
	return (t);
}

static char *ft_only_expand(t_minishell *minishell, char *s)
{
	char *temp;
	char *dup;
	char *join;
	char *sp;
	char a;

	temp = ft_strchr_exp(s, '$');
	a = ft_find_special_char(temp);
	temp = ft_strdup(temp);
	sp = ft_strchr(temp, a);
	sp = ft_strdup(sp);
	join = ft_strtrim(temp, sp);
	free(temp);
	temp = ft_strdup(ft_find_dir(minishell, join));
	dup = ft_substr(s, 0, ft_strlen(s) - ft_strlen(ft_strchr(s, '$')));
	free (join);
	return (ft_change_token(dup, temp, sp));
}

void	ft_expander(t_minishell *minishell)
{
	t_token *temp;
	int i;
	char *t;

	i = 1;
	temp = minishell->tokens;
	while(minishell->tokens)
	{
		if (!ft_strchr(minishell->tokens->token_value, '$') && !ft_strchr(minishell->tokens->token_value, '\"') && !ft_strchr(minishell->tokens->token_value, '\''))
			ft_printf("Token %i: %s OKEY\n", i, minishell->tokens->token_value);
		else
		{
			if (ft_strchr(minishell->tokens->token_value, '$') && !ft_strchr(minishell->tokens->token_value, '\"') && !ft_strchr(minishell->tokens->token_value, '\''))
			{
				ft_printf("Token %i: %s NECESITA SOLO EXPANSION\n", i, minishell->tokens->token_value);
				t = ft_only_expand(minishell, minishell->tokens->token_value);
				free(minishell->tokens->token_value);
				minishell->tokens->token_value = ft_strdup(t);
				free(t);
			}
			else if (ft_strchr(minishell->tokens->token_value, '$') && (ft_strchr(minishell->tokens->token_value, '\"') || ft_strchr(minishell->tokens->token_value, '\'')))
				ft_printf("Token %i: %s NECESITA GESTIONAR COMILLAS Y EXPANSION\n", i, minishell->tokens->token_value);
			else
				ft_printf("Token %i: %s NECESITA SOLO GESTIONAR COMILLAS\n", i, minishell->tokens->token_value);
		}
		i++;
		minishell->tokens = minishell->tokens->next; 
	}
	minishell->tokens = temp;
	ft_print_tokens(minishell->tokens);
}
