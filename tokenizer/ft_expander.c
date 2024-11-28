/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:04:17 by pabromer          #+#    #+#             */
/*   Updated: 2024/11/28 23:28:13 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_expander" processes all tokens in the shell, expanding 
 * variables and handling special cases like quoted content.
 * 
 * - Iterates through the token list and processes each token with `$`, 
 *   single quotes, or double quotes.
 * - Calls `ft_expander_action` to handle individual token expansion.
 * 
 * @param t_minishell *minishell	The shell's state structure.
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

// char	*ft_expand_dquotes(t_minishell *minishell, char *segment)
// {
// 	char	*expanded;
// 	char	*env_value;
// 	int		start;
// 	int		i;
// 	int		new_size;

// 	expanded = ft_calloc(1, 1);
// 	new_size = 1;
// 	i = 0;
// 	while (segment[i])
// 	{
// 		if (segment[i] == '$' && segment[i + 1] != '\0')
// 		{
// 			start = ++i;
// 			while (segment[i] && (ft_isalnum(segment[i]) || segment[i] == '_'))
// 				i++;
// 			char *var_name = ft_substr(segment, start, i - start);
// 			env_value = ft_find_dir(minishell, var_name);
// 			free(var_name);
// 			if (env_value)
// 			{
// 				new_size += ft_strlen(env_value);
// 				expanded = ft_realloc(expanded, new_size - ft_strlen(env_value) - 1, new_size);
// 				ft_memmove(expanded + ft_strlen(expanded), env_value, ft_strlen(env_value));
// 			}
// 		}
// 		else
// 		{
// 			start = i;
// 			while (segment[i] && segment[i] != '$')
// 				i++;
// 			char *literal = ft_substr(segment, start, i - start);
// 			new_size += ft_strlen(literal);
// 			expanded = ft_realloc(expanded, new_size - ft_strlen(literal) - 1, new_size);
// 			ft_memmove(expanded + ft_strlen(expanded), literal, ft_strlen(literal));
// 			free(literal);
// 		}
// 	}
// 	return expanded;
// }

// static void	ft_expander_action(t_minishell *minishell, t_token *token)
// {
// 	char	*new_value;
// 	char	*expanded_part;
// 	char	*env_value;
// 	int		new_size;
// 	int		i;
// 	int		start;

// 	new_value = ft_calloc(1, 1);
// 	new_size = 1;
// 	i = 0;

// 	while (token->token_value[i])
// 	{
// 		if (token->token_value[i] == '\'')
// 		{
// 			start = ++i;
// 			while (token->token_value[i] && token->token_value[i] != '\'')
// 				i++;
// 			char *segment = ft_substr(token->token_value, start, i - start);
// 			new_size += ft_strlen(segment);
// 			new_value = ft_realloc(new_value, new_size - ft_strlen(segment) - 1, new_size);
// 			ft_memmove(new_value + ft_strlen(new_value), segment, ft_strlen(segment));
// 			free(segment);
// 			if (token->token_value[i] == '\'')
// 				i++;
// 		}
// 		else if (token->token_value[i] == '\"')
// 		{
// 			start = ++i;
// 			while (token->token_value[i] && token->token_value[i] != '\"')
// 			{
// 				if (token->token_value[i] == '$')
// 				{
// 					start = ++i;
// 					if (token->token_value[start] == '?')
// 					{
// 						i++;
// 						char *status_str = ft_itoa(minishell->exit);
// 						new_size += ft_strlen(status_str);
// 						new_value = ft_realloc(new_value, new_size - ft_strlen(status_str) - 1, new_size);
// 						ft_memmove(new_value + ft_strlen(new_value), status_str, ft_strlen(status_str));
// 						free(status_str);
// 					}
// 					else
// 					{
// 						while (token->token_value[i] && (ft_isalnum(token->token_value[i]) || token->token_value[i] == '_'))
// 							i++;
// 						expanded_part = ft_substr(token->token_value, start, i - start);
// 						env_value = ft_find_dir(minishell, expanded_part);
// 						free(expanded_part);
// 						if (env_value)
// 						{
// 							new_size += ft_strlen(env_value);
// 							new_value = ft_realloc(new_value, new_size - ft_strlen(env_value) - 1, new_size);
// 							ft_memmove(new_value + ft_strlen(new_value), env_value, ft_strlen(env_value));
// 						}
// 					}
// 				}
// 				else
// 				{
// 					start = i;
// 					while (token->token_value[i] && token->token_value[i] != '$' && token->token_value[i] != '\"')
// 						i++;
// 					char *literal = ft_substr(token->token_value, start, i - start);
// 					new_size += ft_strlen(literal);
// 					new_value = ft_realloc(new_value, new_size - ft_strlen(literal) - 1, new_size);
// 					ft_memmove(new_value + ft_strlen(new_value), literal, ft_strlen(literal));
// 					free(literal);
// 				}
// 			}
// 			if (token->token_value[i] == '\"')
// 				i++;
// 		}
// 		else if (token->token_value[i] == '$')
// 		{
// 			start = ++i;
// 			if (token->token_value[start] == '?')
// 			{
// 				i++;
// 				char *status_str = ft_itoa(minishell->exit);
// 				new_size += ft_strlen(status_str);
// 				new_value = ft_realloc(new_value, new_size - ft_strlen(status_str) - 1, new_size);
// 				ft_memmove(new_value + ft_strlen(new_value), status_str, ft_strlen(status_str));
// 				free(status_str);
// 			}
// 			else
// 			{
// 				while (token->token_value[i] && (ft_isalnum(token->token_value[i]) || token->token_value[i] == '_'))
// 					i++;
// 				expanded_part = ft_substr(token->token_value, start, i - start);
// 				env_value = ft_find_dir(minishell, expanded_part);
// 				free(expanded_part);
// 				if (env_value)
// 				{
// 					new_size += ft_strlen(env_value);
// 					new_value = ft_realloc(new_value, new_size - ft_strlen(env_value) - 1, new_size);
// 					ft_memmove(new_value + ft_strlen(new_value), env_value, ft_strlen(env_value));
// 				}
// 			}
// 		}
// 		else
// 		{
// 			start = i;
// 			while (token->token_value[i] && token->token_value[i] != '$' \
// 					&& token->token_value[i] != '\'' && token->token_value[i] != '\"')
// 				i++;
// 			char *segment = ft_substr(token->token_value, start, i - start);
// 			new_size += ft_strlen(segment);
// 			new_value = ft_realloc(new_value, new_size - ft_strlen(segment) - 1, new_size);
// 			ft_memmove(new_value + ft_strlen(new_value), segment, ft_strlen(segment));
// 			free(segment);
// 		}
// 	}
// 	free(token->token_value);
// 	token->token_value = new_value;
// }

static void ft_handle_single_quotes(const char *token_value, int *i, char **new_value, int *new_size)
{
	int start = ++(*i);
	while (token_value[*i] && token_value[*i] != '\'')
		(*i)++;
	char *segment = ft_substr(token_value, start, *i - start);
	*new_size += ft_strlen(segment);
	*new_value = ft_realloc(*new_value, *new_size - ft_strlen(segment) - 1, *new_size);
	ft_memmove(*new_value + ft_strlen(*new_value), segment, ft_strlen(segment));
	free(segment);
	if (token_value[*i] == '\'')
		(*i)++;
}

static void ft_handle_dollar_sign(t_minishell *minishell, const char *token_value, int *i, char **new_value, int *new_size)
{
	int start = ++(*i);
	if (token_value[start] == '?')
	{
		(*i)++;
		char *status_str = ft_itoa(minishell->exit);
		*new_size += ft_strlen(status_str);
		*new_value = ft_realloc(*new_value, *new_size - ft_strlen(status_str) - 1, *new_size);
		ft_memmove(*new_value + ft_strlen(*new_value), status_str, ft_strlen(status_str));
		free(status_str);
	}
	else
	{
		while (token_value[*i] && (ft_isalnum(token_value[*i]) || token_value[*i] == '_'))
			(*i)++;
		char *expanded_part = ft_substr(token_value, start, *i - start);
		char *env_value = ft_find_dir(minishell, expanded_part);
		free(expanded_part);
		if (env_value)
		{
			*new_size += ft_strlen(env_value);
			*new_value = ft_realloc(*new_value, *new_size - ft_strlen(env_value) - 1, *new_size);
			ft_memmove(*new_value + ft_strlen(*new_value), env_value, ft_strlen(env_value));
		}
	}
}

static void ft_handle_double_quotes(t_minishell *minishell, const char *token_value, int *i, char **new_value, int *new_size)
{
	int start = ++(*i);
	while (token_value[*i] && token_value[*i] != '"')
	{
		if (token_value[*i] == '$')
		{
			ft_handle_dollar_sign(minishell, token_value, i, new_value, new_size);
		}
		else
		{
			start = *i;
			while (token_value[*i] && token_value[*i] != '$' && token_value[*i] != '"')
				(*i)++;
			char *literal = ft_substr(token_value, start, *i - start);
			*new_size += ft_strlen(literal);
			*new_value = ft_realloc(*new_value, *new_size - ft_strlen(literal) - 1, *new_size);
			ft_memmove(*new_value + ft_strlen(*new_value), literal, ft_strlen(literal));
			free(literal);
		}
	}
	if (token_value[*i] == '"')
		(*i)++;
}

static void ft_handle_literal_segment(const char *token_value, int *i, char **new_value, int *new_size)
{
	int start = *i;
	while (token_value[*i] && token_value[*i] != '$' && token_value[*i] != '\'' && token_value[*i] != '\"')
		(*i)++;
	char *segment = ft_substr(token_value, start, *i - start);
	*new_size += ft_strlen(segment);
	*new_value = ft_realloc(*new_value, *new_size - ft_strlen(segment) - 1, *new_size);
	ft_memmove(*new_value + ft_strlen(*new_value), segment, ft_strlen(segment));
	free(segment);
}

static void ft_expander_action(t_minishell *minishell, t_token *token)
{
	char *new_value = ft_calloc(1, 1);
	int new_size = 1;
	int i = 0;

	while (token->token_value[i])
	{
		if (token->token_value[i] == '\'')
			ft_handle_single_quotes(token->token_value, &i, &new_value, &new_size);
		else if (token->token_value[i] == '"')
			ft_handle_double_quotes(minishell, token->token_value, &i, &new_value, &new_size);
		else if (token->token_value[i] == '$')
			ft_handle_dollar_sign(minishell, token->token_value, &i, &new_value, &new_size);
		else
			ft_handle_literal_segment(token->token_value, &i, &new_value, &new_size);
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
