/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:31:22 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/10/29 11:35:10 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_check_operators" Checks if the character at the given index
 * in the line is an operator (<, >, |) and if it is outside of quotes.
 * 
 * @param char *line		The string to be checked, representing a command 
 * 							line.
 * @param int index			The position in the string to check for an 
 * 							operator. 
 * 
 * The function "ft_skip_spaces" advances the index in the given string "line"
 * to skip any whitespace characters. It handles spaces (ASCII 32) as well
 * as other whitespace characters like tabs, newlines, carriage returns, etc. 
 * 
 * @param char *line		The input string where spaces are being skipped.
 * @param int *index		A pointer to the integer index that indicates the
 *							current position in the string. The function will
 *							increment the index to skip over any whitespace 
 * 							characters. 
 * 							The value pointed to by this index will be 
 * 							updated in place.
 * 
 * The function "ft_print_tokens" prints out the list of tokens, displaying 
 * the token value and its type for each token in the list. This function 
 * is useful for debugging and understanding how the input line has been 
 * tokenized.
 * 
 * @param t_token *tokens	A pointer to the head of the linked list of 
 * 							tokens. 
 * 							Each token in the list has a value and type that 
 * 							will be printed.
 * 
 * The function "ft_update_type_tokens" pdates the type of a given token based 
 * on its value and its position in the sequence of tokens. It categorizes the 
 * token into different types such as redirections, pipes, commands, or 
 * arguments.
 * 
 * @param t_token *token	A pointer to the token whose type needs to be 
 * 							updated. 
 * 							The function checks the token's value and the types 
 * 							of its previous tokens to assign the correct type.
 * 
 */

int	ft_check_operators(char *line, int index)
{
	if (ft_strchr("<>|", line[index]) && ft_checker_quotes(line, index) == 0)
		return (1);
	return (0);
}

void	ft_skip_spaces(char *line, int *index)
{
	while (line[*index] == 32 || (line[*index] >= 9 && line[*index] <= 13))
		(*index)++;
}

void	ft_print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		ft_printf(GREEN "###...Running Tokenization...###\n" RESET);
		ft_printf(BLUE "Token: " RESET YELLOW "[%s]\n" RESET BLUE "Type: " \
		RESET YELLOW "[%d]\n\n" RESET, current->token_value, \
		current->token_type);
		current = current->next;
	}
}

static void	ft_empty_tok_out(t_token *tokens)
{
	if (ft_strcmp(tokens->token_value, "") == 0 || \
	ft_strcmp(tokens->token_value, " ") == 0)
		tokens->token_type = TOKEN_EMPTY;
	ft_printf("error: parser: there is an empty token\n");
	return ;
}

void	ft_update_type_tokens(t_token *token)
{
	if (ft_strcmp(token->token_value, "") == 0)
		ft_empty_tok_out(token);
	else if (ft_strcmp(token->token_value, ">") == 0)
		token->token_type = TOKEN_REDIR_STDOUT;
	else if (ft_strcmp(token->token_value, "<") == 0)
		token->token_type = TOKEN_REDIR_STDIN;
	else if (ft_strcmp(token->token_value, ">>") == 0)
		token->token_type = TOKEN_REDIR_APPEND;
	else if (ft_strcmp(token->token_value, "<<") == 0)
		token->token_type = TOKEN_REDIR_HEREDOC;
	else if (ft_strcmp(token->token_value, "|") == 0)
		token->token_type = TOKEN_PIPE;
	else if (ft_strchr(token->token_value, '-'))
		token->token_type = TOKEN_OPTION;
	else if (token->prev != NULL && (\
		token->prev->token_type == TOKEN_REDIR_STDIN || \
		token->prev->token_type == TOKEN_REDIR_STDOUT || \
		token->prev->token_type == TOKEN_REDIR_APPEND || \
		token->prev->token_type == TOKEN_REDIR_HEREDOC))
		token->token_type = TOKEN_ARG;
	else if (token->prev == NULL || token->prev->token_type == TOKEN_PIPE)
		token->token_type = TOKEN_COMMAND;
	else
		token->token_type = TOKEN_ARG;
}
