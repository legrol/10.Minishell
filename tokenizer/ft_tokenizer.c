/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid Date        by              +#+  #+#    #+#             */
/*   Updated: 2024/10/21 20:30:00 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_tokenizer" xxx
 * 
 * @param t_minishell *minishell	A pointer to the minishell structure that
 * 									contains the line to be checked.
 * 
 * The function "ft_get_tokens" xxx
 * 
 * @param char *line				xxx 
 * 
 * The function "ft_read_tokens" xxx
 * 
 * @param char *line				xxx
 * @param int *index				xxx
 * 
 * The function "ft_token_size" xxx
 * 
 * @param char *line				xxx
 * @param int *index				xxx
 * 
 * 
 * 
 */

static int	ft_token_size(char *line, int *index)
{
	int		i;
	char	c;
	int		size;

	i = 0;
	c = 32;
	size = 0;
	while (line[*index + i] && (line[*index + i] != 32 || c != 32))
	{
		if (c == 32 && (line[*index + i] == '\'' || line[*index + i] == '\"' ))
		{
			c = line[*index + i];
			i++;
		}
		else if (c != 32 && line[*index + i] == c)
		{
			size += 2;
			c = 32;
			i++;
		}
		else
			i++;
	}
	return (i - size + 1);
}

static void	ft_fill_token(t_token *token, char *line, int *index)
{
	int		i;
	char	c;

	i = 0;
	c = 32;
	while (line[*index] && (line[*index] != 32 || c != 32))
	{
		if ((line[*index] == '"' || line[*index] == '\'') && c == 32)
			c = line[(*index)++];
		else if (line[*index] == c)
		{
			c = 32;
			(*index)++;
		}
		else
			token->token_value[i++] = line[(*index)++];
	}
	token->token_value[i] = '\0';
}

static t_token	*ft_read_tokens(char *line, int *index)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->token_value = malloc(sizeof(char) * token_size(line, index));
	if (!token->token_value)
	{
		free(token);
		return (NULL);
	}
	ft_fill_token(token, line, index);
	return (token);
}

static t_token	*ft_get_tokens(char *line)
{
	int		i;
	t_token	*token;
	t_token	*prev;

	i = 0;
	ft_skip_spaces(line, &i);
	while (line[i])
	{
		token = ft_read_tokens(line, &i);
		token->prev = token;
		if (prev)
			prev->next = token;
		token->prev = prev;
		prev = token;
		ft_update_type_tokens(token); 	//
		ft_pass_spaces(line, &i);		//
	}
	if (token)
		token->next = NULL;
	while (token && token->prev)
		token = token->prev;
	return (token);

}

t_ast	*ft_tokenizer(t_minishell *minishell)
{
	t_ast	*ast;

	ft_init_signals();
	minishell->line = readline(PROMPT);
	if (!minishell->line)
	{
		minishell->exit = 1;
		ft_putendl_fd("exit", STDERR_FILENO);
		return (NULL);
	}
	if (*minishell->line)
		add_history(minishell->line);
	if (ft_checker_quotes_unclosed(minishell))
	{
		free(minishell->line);
		return (NULL);
	}
	minishell->tokens = ft_get_tokens(minishell->line);
	ft_print_tokens(minishell->tokens);  				 //
	ast = ft_making_ast(minishell->tokens);
	if (ast)
		ft_print_ast(ast);
	free(minishell->line);
	return (ast);
}
