/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:33:21 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/21 22:08:50 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The "main" function of minishell program.
 * 
 * @param int argc 			Number of arguments the program receives from the 
 * 							command line. This is expected to be 1 (just the 
 * 							program name), otherwise an error message is 
 * 							displayed.
 * @param char **argv		String array containing the arguments passed to the 
 * 							program. This program does not take any additional 
 * 							arguments beyond the program name, and passing more
 * 							than that results in an error.
 * @param char **envp		String array containing the system environment 
 * 							variables. These are needed for initializing the 
 * 							`t_minishell` structure and managing the shell 
 * 							environment.
 * 
 * NOTE: g_signals.start 	Integer what indicates the minishell was 
 * 							initialized.
 * 
 * The function "ft_init_envp" initializes the envp inside the minishell 
 * structure. This function takes an array of environment variables (`envp`)
 * and duplicates each entry into the `minishell->envp` array within the 
 * `t_minishell` structure. The function calculates the number of entries
 * in `envp`, allocates memory for each variable, and duplicates them 
 * individually, adding a NULL pointer at the end. 
 * 
 * @param t_minishell *minishell	Pointer to the main minishell structure
 *                                  where the environment variables will 
 *                                  be stored.
 * @param char **envp				Array of environment variables passed
 *                                  to the program by the operating system.
 *  
 * NOTE: t_signal g_signals			Is a global variable that handles input 
 * 									signals. It must be accessible from any 
 * 									area of ​​the minishell program, hence its
 * 									global nature.
 * 
 */

t_signal g_signals;

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;
	int			i;
	t_ast		*ast;

	i = 0;
	(void)argc;
	(void)argv;
	if (argc != 1 || argv[1])
		ft_manage_err(YELLOW NUM_ARGV_ERR RESET);
	ft_print_init();
	ft_init_envp(&minishell, envp);
	while (1)
	{
		if (g_signals.start != 1)
		{
			ft_init_struc_sig(&g_signals);
			ft_init_signals(&minishell);
			ft_init_minishell(&minishell);
		}
		minishell.line = readline(minishell.dirprompt);
		ft_handle_eof(minishell.line);		
		ft_check_empty_line(&minishell);
		if (!minishell.line || ft_checker_quotes_unclosed(&minishell) \
		|| *minishell.line == '\0')
		{
			free(minishell.line);
			minishell.line = NULL;
			continue ;
		}
		ft_tokenizer(&minishell);
		if (ft_syntax_error(&minishell) != -1)
		{
			ast = ft_ast(&minishell);
			ft_exec_ast(&minishell, ast);
			free(minishell.line);
			minishell.line = NULL;
			ft_free_tokens(minishell.tokens);
			minishell.tokens = NULL;
			if (i == 1)
				break ;
		}
	}
	rl_clear_history();
	ft_free_minishell(&minishell);
	if (minishell.dirprompt)
	{
		free(minishell.dirprompt);
		minishell.dirprompt = NULL;
	}

	if (g_signals.dupdirprompt)
	{
		free(g_signals.dupdirprompt);
		g_signals.dupdirprompt = NULL;
	}
	return (0);
}
