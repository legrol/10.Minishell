/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:33:21 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/26 14:56:14 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The main entry point for the `minishell` program. It initializes the shell's 
 * environment, processes user input in an infinite loop, and handles shell 
 * commands while managing memory and errors.
 * 
 * - Validates the arguments and ensures the program is started with no extra 
 *   parameters (`argc == 1` and no `argv[1]`).
 * - Initializes the shell's environment variables and prints the shell's 
 *   startup message.
 * - Enters an infinite loop to handle user input:
 *   - Initializes signal handling and shell structures if the shell is not 
 *     already started.
 *   - Reads input from the user (`readline`) and handles the EOF signal.
 *   - Skips empty lines or lines with unclosed quotes.
 *   - Tokenizes and expands the user input for further processing.
 *   - Checks for syntax errors before building and executing the Abstract 
 *     Syntax Tree (AST).
 *   - Executes the AST and cleans up resources after execution.
 * - Exits the loop and cleans up all allocated resources when the shell 
 *   session ends.
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
 * @return int				Returns `0` to indicate successful program 
 * 							termination.
 * 
 * NOTE: g_signals.start 	Integer what indicates the minishell was 
 * 							initialized.
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
		ft_expander(&minishell);
		if (ft_syntax_error(&minishell) != -1)
		{
			ast = ft_ast(&minishell);
			ft_exec_ast(&minishell, ast);
			free(minishell.line);
			minishell.line = NULL;
			//ft_free_tokens(minishell.tokens);
			//minishell.tokens = NULL;
			if (i == 1)
				break ;
		}
	}
	rl_clear_history();
	ft_free_minishell(&minishell);
	return (0);
}
