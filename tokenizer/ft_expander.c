/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/11/25 15:04:17 by pabromer         ###   ########.fr       */
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

static char *ft_change_token(char *temp, char *sp)
{
	char *t;
	char *join;

	if (!temp)
		join = ft_strdup(sp);
	else
		join = ft_strjoin(temp, sp);
	t = ft_strdup(join);
	if (temp)
		free(temp);
	free(join);
	free(sp);
	return (t);
}

static char *ft_only_expand_join(t_minishell *minishell, char *join, int f)
{
	char *temp;

	if (f == 1)
		temp = ft_itoa(minishell->exit);
	else
	{
		if (ft_find_dir(minishell, join))
			temp = ft_strdup(ft_find_dir(minishell, join));
		else
		temp = NULL;
	}
	return (temp);
}

static char *ft_only_expand(t_minishell *minishell, char *s)
{
	char *temp;
	char *join;
	char *sp;
	char a;
	int f;

	f = 0;
	temp = ft_strchr_exp(s, '$');
	a = ft_find_special_char(temp);
	temp = ft_strdup(temp);
	if (temp && temp[0] == '?')
	{
		f = 1;
		sp = ft_strchr_exp(temp, '?');
	}
	else
		sp = ft_strchr(temp, a);
	sp = ft_strdup(sp);
	join = ft_strtrim(temp, sp);
	free(temp);
	temp = ft_only_expand_join(minishell, join, f);
	free (join);
	return (ft_change_token(temp, sp));
}

static int ft_count_dollar(char *s)
{
	int c;
	int i;

	i = 0;
	c = 0;
	while(s[i])
	{
		if(s[i] == '$')
			c++;
		i++;
	}
	return (i+c+1);
}

static char *ft_prepare_split(char *s)
{
	int c;
	int i;
	char *temp;

	temp = malloc(ft_count_dollar(s)*sizeof(char));
	i = 0;
	c = 0;
	while(s[i])
	{
		if(s[i] == '$')
		{
			temp[c+i] = '\n';
			c++;
		}
		temp[c+i] = s[i];
		i++;
	}
	temp[c+i] = '\0';
	return (temp);
}

char *ft_split_expand_join(char **split)
{
	char *temp;
	char *temp2;
	int i;

	temp = split[0];
	i = 1;
	while(split[i])
	{
		temp2 = ft_strjoin(temp, split[i]);
		free(temp);
		temp = temp2;
		i++;
	}
	i = 0;
	/*while (split[i])
	{
		free(split[i]);
		i++;
	}
	//free(split);*/
	return (temp);
}

char *ft_split_expand(t_minishell *minishell, char *s)
{
	char *temp;
	char **split;
	char *temp2;
	int i;

	temp = ft_prepare_split(s);
	split = ft_split(temp, '\n');
	i = 0;
	while(split[i])
	{
		if (ft_strchr(split[i], '$'))
		{
			temp2 = ft_only_expand(minishell, split[i]);
			free(split[i]);
			split[i] = temp2;
		}
		i++;
	}
	if (temp)
		free(temp);
	temp = ft_split_expand_join(split);
	free(split);
	return (temp);
}

static void	ft_expander_action(t_minishell *minishell)
{
	char *t;

	if (ft_strchr(minishell->tokens->token_value, '$') \
		&& !ft_strchr(minishell->tokens->token_value, '\"') \
		&& !ft_strchr(minishell->tokens->token_value, '\''))
	{
		t = ft_split_expand(minishell, minishell->tokens->token_value);
		free(minishell->tokens->token_value);
		minishell->tokens->token_value = ft_strdup(t);
		free(t);
	}
	else
	{
		t = split_substrings(minishell, minishell->tokens->token_value);
		free(minishell->tokens->token_value);
		minishell->tokens->token_value = ft_strdup(t);
		free(t);
	}
}

void	ft_expander(t_minishell *minishell)
{
	t_token *temp;
	int i;

	i = 1;
	temp = minishell->tokens;
	while(minishell->tokens)
	{
		if (ft_strchr(minishell->tokens->token_value, '$') \
		|| ft_strchr(minishell->tokens->token_value, '\"') \
		|| ft_strchr(minishell->tokens->token_value, '\''))
			ft_expander_action(minishell);
		i++;
		minishell->tokens = minishell->tokens->next; 
	}
	minishell->tokens = temp;
	ft_print_tokens(minishell->tokens);
}
