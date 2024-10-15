/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:50:51 by pabromer          #+#    #+#             */
/*   Updated: 2024/10/15 16:11:55 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free_copy(char **ent)
{
	int	i;

	i = 0;
	while(ent[i])
	{
		free(ent[i]);
		i++;
	}
	free(ent);
}

int main(int argc, char **argv, char **env) {
    
	char *input;
	char *p;
	char *prompt;
	char **ent;

	if (argc > 1)
	{
		ft_printf("minishell doesnt need arguments like %s", argv[1]);
		return 0;
	}
	ent = ft_cp_ent(env);
	prompt = "pabromer-rdel-olm minishell:~";
	p = ft_strjoin(prompt, ft_find_dir(env, "PWD"));
	prompt = ft_strjoin(p, "$ ");
	free (p);
    while (1) 
    { 
        input = readline(prompt);
		if (input[0] == 'e' && input[1] == 'c' && input[2] == 'h' && input[3] == 'o' && input[4] == '\0')
			ft_echo(input);
		else if (input[0] == 'c' && input[1] == 'd' && input[2] == ' ')
		{
			free(prompt);
			prompt = ft_cd(input, ent);
		}
		/*else if (input[0] == 'e' && input[1] == 'x' && input[2] == 'p' && input[3] == 'o' && input[4] == 'r' && input[5] == 't' && input[6] == '\0')
			ft_export;
		else if (input[0] == 'u' && input[1] == 'n' && input[2] == 's' && input[3] == 'e' && input[4] == 't' && input[5] == '\0')
			ft_unset;*/
		else if (input[0] == 'e' && input[1] == 'n' && input[2] == 'v' && input[3] == '\0')
			ft_env(ent);
		else if (input[0] == 'e' && input[1] == 'x' && input[2] == 'i' && input[3] == 't' && input[4] == '\0')
		{
			ft_printf("exit\n");
			break;
		}
		else
        	ft_cmdexe(env, input);
		free(input);
    }
	ft_free_copy(ent);
	free(prompt);
	free(input);
    return 0;
}

