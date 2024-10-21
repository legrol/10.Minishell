/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 09:33:41 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/10/21 10:14:45 by pabromer         ###   ########.fr       */
/*   Created: 2024/10/17 09:33:41 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/10/21 10:14:45 by pabromer         ###   ########.fr       */
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
 */

static t_token	*ft_read_tokens(char *line, int *i)
{
	t_token	*token;
	int		i;
	char	c;

	i = 0;
	c = 32;



	while()
	{


	}

	return (token);
}

static t_token	*ft_get_tokens(char *line)
{
	int		i;
	t_token	*token;

	i = 0;
	ft_skip_spaces(line, &i);
	while (line[i])
	{
		token = ft_read_tokens(line, &i);

	}


}

void	ft_tokenizer(t_minishell *minishell)
{

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


}
