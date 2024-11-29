/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:04:17 by pabromer          #+#    #+#             */
/*   Updated: 2024/11/29 01:23:27 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "" xxxxx
 * 
 * @param xxxx
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */

void	*ft_realloc(void *p, int old_size, int new_size)
{
	void	*r;

	if (!new_size)
		return (free(p), NULL);
	r = ft_calloc(1, new_size);
	if (p && old_size <= new_size)
		ft_memmove(r, p, old_size);
	else if (p && old_size > new_size)
		ft_memmove(r, p, new_size);
	return (free(p), r);
}

static void	ft_handle_single_quotes(const char *token_value, int *i, \
char **new_value, int *new_size)
{
	int		start;
	char	*segment;

	start = ++(*i);
	while (token_value[*i] && token_value[*i] != '\'')
		(*i)++;
	segment = ft_substr(token_value, start, *i - start);
	*new_size += ft_strlen(segment);
	*new_value = ft_realloc(*new_value, *new_size - ft_strlen(segment) - 1, \
	*new_size);
	ft_memmove(*new_value + ft_strlen(*new_value), segment, \
	ft_strlen(segment));
	free(segment);
	if (token_value[*i] == '\'')
		(*i)++;
}

static void	ft_append_to_new_value(char **new_value, const char *to_append)
{
	size_t	old_len;
	size_t	append_len;
	size_t	new_len;

	old_len = ft_strlen(*new_value);
	append_len = ft_strlen(to_append);
	new_len = old_len + append_len + 1;
	*new_value = ft_realloc(*new_value, old_len, new_len);
	ft_memmove(*new_value + old_len, to_append, append_len);
	(*new_value)[new_len - 1] = '\0';
}

static void	ft_expand_status(t_minishell *minishell, char **new_value)
{
	char	*status_str;

	status_str = ft_itoa(minishell->exit);
	ft_append_to_new_value(new_value, status_str);
	free(status_str);
}

static void	ft_expand_variable(t_minishell *minishell, const \
char *token_value, int *i, char **new_value)
{
	int		start;
	char	*var_name;
	char	*env_value;

	start = *i;
	while (token_value[*i] && (ft_isalnum(token_value[*i]) || \
	token_value[*i] == '_'))
		(*i)++;
	var_name = ft_substr(token_value, start, *i - start);
	env_value = ft_find_dir(minishell, var_name);
	free(var_name);
	if (env_value)
		ft_append_to_new_value(new_value, env_value);
}

static void	ft_handle_dollar_sign(t_minishell *minishell, \
const char *token_value, int *i, char **new_value)
{
	(*i)++;
	if (token_value[*i] == '?')
	{
		(*i)++;
		ft_expand_status(minishell, new_value);
	}
	else
		ft_expand_variable(minishell, token_value, i, new_value);
}

static void	ft_handle_literal_in_quotes(const char *token_value, int *i, \
char **new_value)
{
	int		start;
	char	*literal;

	start = *i;
	while (token_value[*i] && token_value[*i] != '$' && token_value[*i] != '\"')
		(*i)++;
	literal = ft_substr(token_value, start, *i - start);
	ft_append_to_new_value(new_value, literal);
	free(literal);
}

static void	ft_handle_double_quotes(t_minishell *minishell, const char \
*token_value, int *i, char **new_value)
{
	(*i)++;
	while (token_value[*i] && token_value[*i] != '\"')
	{
		if (token_value[*i] == '$')
			ft_handle_dollar_sign(minishell, token_value, i, new_value);
		else
			ft_handle_literal_in_quotes(token_value, i, new_value);
	}
	if (token_value[*i] == '\"')
		(*i)++;
}

static void	ft_advance_to_special_char(const char *token_value, int *i)
{
	while (token_value[*i] && token_value[*i] != '$' && token_value[*i] \
	!= '\'' && token_value[*i] != '\"')
		(*i)++;
}

static void	ft_handle_literal_segment(const char *token_value, int *i, \
char **new_value)
{
	int		start;

	start = *i;
	ft_advance_to_special_char(token_value, i);
	ft_append_to_new_value(new_value, ft_substr(token_value, start, *i \
	- start));
}

static void	ft_expander_action(t_minishell *minishell, t_token *token)
{
	char	*new_value;
	int		new_size;
	int		i;

	new_value = ft_calloc(1, 1);
	new_size = 1;
	i = 0;
	while (token->token_value[i])
	{
		if (token->token_value[i] == '\'')
			ft_handle_single_quotes(token->token_value, &i, &new_value, \
			&new_size);
		else if (token->token_value[i] == '\"')
			ft_handle_double_quotes(minishell, token->token_value, &i, \
			&new_value);
		else if (token->token_value[i] == '$')
			ft_handle_dollar_sign(minishell, token->token_value, &i, \
			&new_value);
		else
			ft_handle_literal_segment(token->token_value, &i, &new_value);
	}
	free(token->token_value);
	token->token_value = new_value;
}

void	ft_expander(t_minishell *minishell)
{
	t_token	*temp;

	temp = minishell->tokens;
	while (minishell->tokens)
	{
		if (ft_strchr(minishell->tokens->token_value, '$') || \
			ft_strchr(minishell->tokens->token_value, '\"') || \
			ft_strchr(minishell->tokens->token_value, '\''))
		{
			ft_expander_action(minishell, minishell->tokens);
		}
		minishell->tokens = minishell->tokens->next;
	}
	minishell->tokens = temp;
	ft_print_tokens(minishell->tokens);
}
