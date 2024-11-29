/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:33:21 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/27 10:22:23 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The "main" function is the entry point of the program. It initializes the
 * `minishell` environment, processes user input in a loop, and manages
 * cleanup upon termination.
 * 
 * @param int argc					The argument count passed to the program.
 * @param char **argv				The argument vector containing command-line 
 * 									arguments.
 * @param char **envp				An array of strings representing the 
 * 									environment variables.
 * @return int						Returns the terminal status upon exit.
 * 
 * The function "ft_process_line" processes the input line from the `minishell`
 * structure. It handles EOF, checks for empty lines, expands variables, and
 * executes commands using the Abstract Syntax Tree (AST) if there are no 
 * syntax errors.
 * 
 * @param t_minishell *minishell	A pointer to the minishell structure that
 * 									contains the input line, tokens, and 
 * 									other state variables.
 * @param t_ast **ast				A pointer to the AST structure to be
 * 									generated and executed.
 * @return int						Returns 0 if the line is empty or invalid,
 * 									1 otherwise.
 * 
 * The function "ft_handle_signals_and_structs" initializes the signal handling
 * and other necessary structures in the `minishell` environment. This is only
 * executed if signals are not already initialized.
 * 
 * @param t_minishell *minishell	A pointer to the minishell structure used
 * 									to manage the current state.
 * @return void
 * 
 * The function "ft_initialize_minishell" initializes the `minishell` structure
 * by printing the startup banner and setting up the environment variables.
 * 
 * @param t_minishell *minishell	A pointer to the minishell structure to be 
 * 									initialized.
 * @param char **envp				An array of strings representing the 
 * 									environment variables passed to the program.
 * @return void
 * 
 * 
 * 
 * NOTE: g_signals.start 	Integer what indicates the minishell was 
 * 							initialized.
 * 
 */

t_signal	g_signals;

static void	ft_initialize_minishell(t_minishell *minishell, char **envp)
{
	ft_print_init();
	ft_init_envp(minishell, envp);
}

static void	ft_handle_signals_and_structs(t_minishell *minishell)
{
	if (g_signals.start != 1)
	{
		ft_init_struc_sig(&g_signals);
		ft_init_signals(minishell);
		ft_init_minishell(minishell);
	}
}

static int	ft_process_line(t_minishell *minishell, t_ast **ast)
{
	ft_handle_eof(minishell->line);
	ft_check_empty_line(minishell);
	if (!minishell->line || ft_checker_quotes_unclosed(minishell) \
	|| *minishell->line == '\0')
	{
		free(minishell->line);
		minishell->line = NULL;
		return (0);
	}
	if (ft_tokenizer(minishell) == 0)
	{
		ft_expander(minishell);
		if (ft_syntax_error(minishell) != -1)
		{
			*ast = ft_ast(minishell);
			ft_exec_ast(minishell, *ast);
		}
		free(minishell->line);
		minishell->line = NULL;
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;
	t_ast		*ast;

	(void)argc;
	(void)argv;
	if (argc != 1 || argv[1])
		ft_manage_err(YELLOW NUM_ARGV_ERR RESET);
	ft_initialize_minishell(&minishell, envp);
	while (1)
	{
		ft_handle_signals_and_structs(&minishell);
		minishell.line = readline(minishell.dirprompt);
		if (!ft_process_line(&minishell, &ast))
			continue ;
	}
	ft_free_minishell(&minishell);
	rl_clear_history();
	return (minishell.terminal_status);
}
