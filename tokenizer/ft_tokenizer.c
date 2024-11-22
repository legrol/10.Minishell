/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:24:31 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/21 13:24:45 by rdel-olm         ###   ########.fr       */
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
 * The function "ft_fill_token" fills the token structure with the value 
 * extracted from the input line.
 *
 * @param t_token *token			A pointer to the token structure to be 
 *									filled with the extracted value.
 * @param char *line				A string representing the input line from 
 *									which the token is extracted.
 * @param int *index				A pointer to the current position in the 
 *									line.
 * 
 * The function "ft_handle_special_char" processes special characters at the 
 * start of a token. It checks for `>>` or `<<` and tokenizes them as a 
 * single token. If neither is found, it handles a single character like `>`, 
 * `<`, or `|`.
 * 
 * @param t_token *token		A pointer to the token structure being filled.
 * @param char *line			The input line containing the characters to be 
 *								processed.
 * @param int *index			A pointer to the current position in the line, 
 *								which will be updated as characters are 
 * 								processed.
 * @param int i					The current position in the token's value.
 * @return int					The updated position in the token's value.
 * 
 */

static int	ft_handle_special_char(t_token *token, char *line, \
int *index, int i)
{
	if (i == 0 && (line[*index] == '>' || line[*index] == '<') \
	&& line[*index] == line[*index + 1])
	{
		token->token_value[i++] = line[(*index)++];
		token->token_value[i++] = line[(*index)++];
	}
	else if (i == 0)
		token->token_value[i++] = line[(*index)++];
	return (i);
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
		else if (ft_strchr("<>|", line[*index]))
		{
			i = ft_handle_special_char(token, line, index, i);
			break ;
		}
		else
			token->token_value[i++] = line[(*index)++];
	}
	token->token_value[i] = '\0';
}

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

// static t_token	*ft_get_tokens(char *line)
// {
// 	int		i;
// 	t_token	*token_gt;
// 	t_token	*prev;

// 	i = 0;
// 	token_gt = NULL;
// 	prev = NULL;
// 	ft_skip_spaces(line, &i);
// 	while (line[i])
// 	{
// 		token_gt = ft_read_tokens(line, &i);
// 		if (!token_gt)
// 			return (ft_free_tokens(prev), NULL);
// 		ft_split_and_update_tokens(token_gt);
// 		if (prev)
// 			prev->next = token_gt;
// 		token_gt->prev = prev;
// 		prev = token_gt;
// 		ft_update_type_tokens(token_gt);
// 		ft_skip_spaces(line, &i);
// 	}
// 	while (token_gt && token_gt->prev)
// 		token_gt = token_gt->prev;
// 	return (token_gt);
// }

static t_token	*ft_get_tokens(char *line)
{
	int		i;
	t_token	*current_token;
	t_token	*prev_token;
	t_token	*head;

	i = 0;
	head = NULL;
	prev_token = NULL;
	ft_skip_spaces(line, &i);
	while (line[i])
	{
		current_token = ft_read_tokens(line, &i);
		if (!current_token)
		{
			ft_free_tokens(head);
			return (NULL);
		}
		if (prev_token)
			prev_token->next = current_token;
		current_token->prev = prev_token;
		if (!head)
			head = current_token;
		prev_token = current_token;
		ft_split_and_update_tokens(current_token);
		ft_update_type_tokens(current_token);
		ft_skip_spaces(line, &i);
	}
	return (head);
}

void	*ft_tokenizer(t_minishell *minishell)
{
	if (!minishell->line)
	{
		minishell->exit = 1;
		ft_putendl_fd(WHITOUT_COMMAND_ERR, STDERR_FILENO);
		free(minishell->line);
		minishell->line = NULL;
		return (NULL);
	}
	if (*minishell->line)
		add_history(minishell->line);
	if (ft_checker_quotes_unclosed(minishell))
		return (NULL);
	ft_free_tokens(minishell->tokens);
	minishell->tokens = ft_get_tokens(minishell->line);
	if (!minishell->tokens)
	{
		free(minishell->line);
		minishell->line = NULL;
		return (NULL);
	}
	ft_print_tokens(minishell->tokens);
	return (NULL);
}
