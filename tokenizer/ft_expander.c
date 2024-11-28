/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:04:17 by pabromer          #+#    #+#             */
/*   Updated: 2024/11/28 17:37:58 by pabromer         ###   ########.fr       */
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
 * The function "ft_expander_action" processes a single token, handling 
 * variable expansion based on its content and context (e.g., quotes).
 * 
 * - Expands variables if `$` is found and the token is not quoted.
 * - Uses `split_substrings` for tokens requiring additional processing.
 * 
 * @param t_minishell *minishell	The shell's state structure.
 * 
 * The function "ft_split_expand" handles splitting a string into substrings 
 * based on `$` and expands each variable found.
 * 
 * - Uses `ft_prepare_split` to format the string with newlines for splitting.
 * - Expands variables using `ft_only_expand` for substrings containing `$`.
 * - Joins the processed substrings into a final result.
 * 
 * @param t_minishell *minishell	The shell's state structure.
 * @param char *s					The input string to process.
 * 
 * @return char*					A dynamically allocated string with all 
 *									variables expanded.
 * 
 * The function "ft_prepare_split" processes a string by adding newlines 
 * (`'\n'`) after each `$` character, preparing it for splitting into 
 * substrings.
 * 
 * - Allocates memory based on the size calculated by `ft_count_dollar`.
 * - Iterates through the input string, copying characters into the new buffer.
 * - Inserts a newline (`'\n'`) after each `$` character to facilitate 
 *   splitting.
 * 
 * - Example:
 *   Input: `"echo $USER"`
 *   Output: `"echo\n$USER"`
 * 
 * @param char *s	The input string to process.
 * 
 * @return char*	A dynamically allocated string with newlines inserted, 
 * 					or `NULL` if memory allocation fails. 
 * 
 * The function "ft_only_expand" handles the expansion of variables in a string.
 * 
 * - Extracts the portion of the string starting with `$` and identifies 
 *   special characters as delimiters.
 * - Expands `$?` using the shell's exit status or retrieves the corresponding 
 *   environment variable.
 * - Combines the expanded value with the rest of the string.
 * 
 * @param t_minishell *minishell	The shell's state structure.
 * @param char *s					The input string containing variables to
 * 									expand.
 * 
 * @return char*					A dynamically allocated string with the 
 * 									expanded value. 
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

/*static char	*ft_only_expand(t_minishell *minishell, char *s)
{
	char	*temp;
	char	*join;
	char	*sp;
	char	a;
	int		f;

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

static char	*ft_prepare_split(char *s)
{
	int		c;
	int		i;
	char	*temp;

	temp = malloc(ft_count_dollar(s) * sizeof(char));
	i = 0;
	c = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			temp[c + i] = '\n';
			c++;
		}
		temp[c + i] = s[i];
		i++;
	}
	temp[c + i] = '\0';
	return (temp);
}

char	*ft_split_expand(t_minishell *minishell, char *s)
{
	char	*temp;
	char	**split;
	char	*temp2;
	int		i;

	temp = ft_prepare_split(s);
	split = ft_split(temp, '\n');
	i = 0;
	while (split[i])
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
	char	*t;

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
	t_token	*temp;

	temp = minishell->tokens;
	while (minishell->tokens)
	{
		if (ft_strchr(minishell->tokens->token_value, '$') \
		|| ft_strchr(minishell->tokens->token_value, '\"') \
		|| ft_strchr(minishell->tokens->token_value, '\''))
			ft_expander_action(minishell);
		minishell->tokens = minishell->tokens->next;
	}
	minishell->tokens = temp;
	ft_print_tokens(minishell->tokens);
}*/

char	*ft_expand_dquotes(t_minishell *minishell, char *segment)
{
	char	*expanded;
	char	*env_value;
	int		start;
	int		i;
	int		new_size;

	expanded = ft_calloc(1, 1); // Inicializa una cadena vacía
	new_size = 1; // Tamaño inicial del buffer
	i = 0;

	while (segment[i])
	{
		if (segment[i] == '$' && segment[i + 1] != '\0') // Detectar variables
		{
			start = ++i;
			while (segment[i] && (ft_isalnum(segment[i]) || segment[i] == '_'))
				i++;
			char *var_name = ft_substr(segment, start, i - start);
			env_value = ft_find_dir(minishell, var_name); // Buscar variable en el entorno
			free(var_name);

			if (env_value)
			{
				new_size += ft_strlen(env_value);
				expanded = ft_realloc(expanded, new_size - ft_strlen(env_value) - 1, new_size);
				ft_memmove(expanded + ft_strlen(expanded), env_value, ft_strlen(env_value));
			}
		}
		else // Copiar texto literal
		{
			start = i;
			while (segment[i] && segment[i] != '$') // Copiar hasta la siguiente variable
				i++;
			char *literal = ft_substr(segment, start, i - start);
			new_size += ft_strlen(literal);
			expanded = ft_realloc(expanded, new_size - ft_strlen(literal) - 1, new_size);
			ft_memmove(expanded + ft_strlen(expanded), literal, ft_strlen(literal));
			free(literal);
		}
	}
	return expanded;
}

void	ft_expander_action(t_minishell *minishell, t_token *token)
{
	char	*new_value;
	char	*expanded_part;
	char	*env_value;
	int		new_size;
	int		i;
	int		start;

	new_value = ft_calloc(1, 1); // Inicializa con cadena vacía
	new_size = 1; // Tamaño inicial (solo para terminador nulo)
	i = 0;

	while (token->token_value[i])
	{
		if (token->token_value[i] == '\'') // Comillas simples: conservar literal
		{
			start = ++i;
			while (token->token_value[i] && token->token_value[i] != '\'')
				i++;
			char *segment = ft_substr(token->token_value, start, i - start);
			new_size += ft_strlen(segment);
			new_value = ft_realloc(new_value, new_size - ft_strlen(segment) - 1, new_size);
			ft_memmove(new_value + ft_strlen(new_value), segment, ft_strlen(segment));
			free(segment);
			if (token->token_value[i] == '\'')
				i++; // Salta la comilla de cierre
		}
		else if (token->token_value[i] == '\"') // Comillas dobles: expandir variables
		{
			start = ++i;
			while (token->token_value[i] && token->token_value[i] != '\"')
			{
				if (token->token_value[i] == '$') // Expandir variables dentro de comillas dobles
				{
					start = ++i;
					if (token->token_value[start] == '?') // Manejo de `$?`
					{
						i++;
						char *status_str = ft_itoa(minishell->exit);
						new_size += ft_strlen(status_str);
						new_value = ft_realloc(new_value, new_size - ft_strlen(status_str) - 1, new_size);
						ft_memmove(new_value + ft_strlen(new_value), status_str, ft_strlen(status_str));
						free(status_str);
					}
					else
					{
						while (token->token_value[i] && (ft_isalnum(token->token_value[i]) || token->token_value[i] == '_'))
							i++;
						expanded_part = ft_substr(token->token_value, start, i - start);
						env_value = ft_find_dir(minishell, expanded_part);
						free(expanded_part);
						if (env_value)
						{
							new_size += ft_strlen(env_value);
							new_value = ft_realloc(new_value, new_size - ft_strlen(env_value) - 1, new_size);
							ft_memmove(new_value + ft_strlen(new_value), env_value, ft_strlen(env_value));
						}
					}
				}
				else // Copiar caracteres literales dentro de comillas dobles
				{
					start = i;
					while (token->token_value[i] && token->token_value[i] != '$' && token->token_value[i] != '\"')
						i++;
					char *literal = ft_substr(token->token_value, start, i - start);
					new_size += ft_strlen(literal);
					new_value = ft_realloc(new_value, new_size - ft_strlen(literal) - 1, new_size);
					ft_memmove(new_value + ft_strlen(new_value), literal, ft_strlen(literal));
					free(literal);
				}
			}
			if (token->token_value[i] == '\"')
				i++; // Salta la comilla de cierre
		}
		else if (token->token_value[i] == '$') // Expandir variables fuera de comillas
		{
			start = ++i;
			if (token->token_value[start] == '?') // Manejo de `$?`
			{
				i++;
				char *status_str = ft_itoa(minishell->exit);
				new_size += ft_strlen(status_str);
				new_value = ft_realloc(new_value, new_size - ft_strlen(status_str) - 1, new_size);
				ft_memmove(new_value + ft_strlen(new_value), status_str, ft_strlen(status_str));
				free(status_str);
			}
			else
			{
				while (token->token_value[i] && (ft_isalnum(token->token_value[i]) || token->token_value[i] == '_'))
					i++;
				expanded_part = ft_substr(token->token_value, start, i - start);
				env_value = ft_find_dir(minishell, expanded_part);
				free(expanded_part);
				if (env_value)
				{
					new_size += ft_strlen(env_value);
					new_value = ft_realloc(new_value, new_size - ft_strlen(env_value) - 1, new_size);
					ft_memmove(new_value + ft_strlen(new_value), env_value, ft_strlen(env_value));
				}
			}
		}
		else // Copiar texto literal fuera de comillas
		{
			start = i;
			while (token->token_value[i] && token->token_value[i] != '$' \
					&& token->token_value[i] != '\'' && token->token_value[i] != '\"')
				i++;
			char *segment = ft_substr(token->token_value, start, i - start);
			new_size += ft_strlen(segment);
			new_value = ft_realloc(new_value, new_size - ft_strlen(segment) - 1, new_size);
			ft_memmove(new_value + ft_strlen(new_value), segment, ft_strlen(segment));
			free(segment);
		}
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

