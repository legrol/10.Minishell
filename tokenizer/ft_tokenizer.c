/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:38:31 by pabromer          #+#    #+#             */
/*   Updated: 2024/11/27 09:52:35 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_tokenizer" tokenizes the input line from the `minishell`
 * structure and creates an abstract syntax tree (AST) from the tokens. It 
 * handles signal initialization, input reading, and basic error checking 
 * (e.g., unclosed quotes).
 * 
 * @param t_minishell *minishell	A pointer to the minishell structure that
 * 									contains the input line and stores the 
 * 									tokens and the generated AST.
 * @return void*					NULL if an error occurs; otherwise, 
 *									processes the tokens.
 * 
 * The function "ft_get_tokens" breaks the input line into a list of tokens, 
 * each of which is processed and stored in a linked list. It skips spaces and 
 * updates token types.
 * 
 * @param char *line				A string containing the input line to be 
 * 									tokenized.
 * @return t_token*					A pointer to the head of the linked list 
 *									of tokens, or NULL if an error occurs.
 * 
 * The function "ft_read_tokens" reads a single token from the input line 
 * and allocates memory for it. It also handles the parsing of quotes and 
 * stores the token in a structure. It is closely related to "ft_fill_token" 
 * (it had to be split into two functions to comply with Standard 42).
 * 
 * @param char *line				A string representing the input line being 
 * 									parsed.
 * @param int *index				A pointer to the current position in the 
 * 									line.
 * @return t_token*					A pointer to the created token structure, 
 *									or NULL if memory allocation fails.
 *  
 * 
 * 
 * 
 * Antes de return (0) de salida de ft_tokenizer esta funcion para depurar 
 * siempre tokens. ---> ft_print_tokens(minishell->tokens);
 */

static t_token	*ft_read_tokens(char *line, int *index)
{
	t_token	*token_rd;
	int		token_size;

	token_rd = malloc(sizeof(t_token));
	if (!token_rd)
		return (NULL);
	token_size = ft_token_size(line, index);
	token_rd->token_value = malloc(sizeof(char) * (token_size + 1));
	if (!token_rd->token_value)
	{
		free(token_rd);
		return (NULL);
	}
	ft_fill_token(token_rd, line, index);
	token_rd->next = NULL;
	token_rd->prev = NULL;
	return (token_rd);
}

static t_token	*ft_get_tokens(char *line)
{
	int		i;
	t_token	*token_gt;
	t_token	*prev;

	i = 0;
	prev = NULL;
	ft_skip_spaces(line, &i);
	if (line[i] == '\0')
		return (NULL);
	while (line[i])
	{
		token_gt = ft_read_tokens(line, &i);
		if (!token_gt)
			return (ft_free_tokens(prev), NULL);
		ft_update_tokens(token_gt);
		if (prev)
			prev->next = token_gt;
		token_gt->prev = prev;
		prev = token_gt;
		ft_update_type_tokens(token_gt);
		ft_skip_spaces(line, &i);
	}
	while (token_gt && token_gt->prev)
		token_gt = token_gt->prev;
	return (token_gt);
}

int	ft_tokenizer(t_minishell *minishell)
{
	if (!minishell->line)
	{
		minishell->exit = 1;
		ft_putendl_fd(WHITOUT_COMMAND_ERR, STDERR_FILENO);
		free(minishell->line);
		minishell->line = NULL;
		return (-1);
	}
	if (*minishell->line)
		add_history(minishell->line);
	if (ft_checker_quotes_unclosed(minishell))
		return (-1);
	ft_free_tokens(minishell->tokens);
	minishell->tokens = ft_get_tokens(minishell->line);
	if (!minishell->tokens)
	{
		free(minishell->line);
		minishell->line = NULL;
		return (-1);
	}
	return (0);
}
