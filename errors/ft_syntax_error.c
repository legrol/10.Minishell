/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:33:21 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/19 17:04:40 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int ft_token_type(int token)
{
	if (token == 1 || token == 2 || token == 3 || token == 4 || token == 8)
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
		{
			ft_printf("Syntax error\n");
			minishell->tokens = temp;
			return (-1);
		}
		else if (minishell->tokens->next && ft_token_type(minishell->tokens->token_type) == 1 \
		&& ft_token_type(minishell->tokens->next->token_type) == 1)
		{
			ft_printf("Syntax error\n");
			minishell->tokens = temp;
			return (-1);
		}
		i++;
		minishell->tokens = minishell->tokens->next; 
	}
	minishell->tokens = temp;
	return (i);
}