/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:33:21 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/25 10:23:31 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int ft_print_syntax_error(t_minishell *minishell, t_token *temp)
{
	ft_printf("Syntax error\n");
	minishell->tokens = temp;
	minishell->exit = 1;
	free(minishell->line);
	return (-1);
}

static int ft_token_type(int token)
{
	if (token == 1 || token == 2 || token == 3 || token == 4 || token == 8)
		return (1);
	return (0);
}

static int ft_check_token_value(t_token *token)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (token->token_value[i])
	{
		if (token->token_value[i] == '.')
			j++;
		i++;
	}
	if (i != 0 && i == j && (!token->prev || token->prev->token_type == 1 \
	|| token->prev->token_type == 2 || token->prev->token_type == 3 \
	|| token->prev->token_type == 4 || token->prev->token_type == 8))
		return (1);
	return (0);

}

int ft_syntax_error(t_minishell *minishell)
{
	int	i;
	t_token *temp;

	temp = minishell->tokens;
	i = 0;

	while(minishell->tokens)
	{
		if (i == 0 && ft_token_type(minishell->tokens->token_type) == 1)
			return (ft_print_syntax_error(minishell, temp));
		else if (minishell->tokens->next && ft_token_type(minishell->tokens->token_type) == 1 \
		&& ft_token_type(minishell->tokens->next->token_type) == 1)
			return (ft_print_syntax_error(minishell, temp));
		else if (!minishell->tokens->next && ft_token_type(minishell->tokens->token_type) == 1)
			return (ft_print_syntax_error(minishell, temp));
		else if (ft_check_token_value(minishell->tokens) == 1)
			return (ft_print_syntax_error(minishell, temp));
		i++;
		minishell->tokens = minishell->tokens->next; 
	}
	minishell->tokens = temp;
	return (i);
}
