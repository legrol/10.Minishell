/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 06:55:30 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/26 10:22:45 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_init_signals" initializes the handler for each signal.
 * 		- 	It first sets the prompt by copying `minishell->dirprompt` into 
 *   		`g_signals.dupdirprompt`, ensuring memory is safely managed.
 * 		- 	The function then assigns `sig_int` and `sig_quit` as handlers for 
 *   		SIGINT and SIGQUIT, respectively.
 * 		- 	Finally, it enables terminal printing functionality.
 * 
 * 		signal(SIGINT, &sig_int) ≡ signal(2, pointer to handler)
 * 		signal(SIGQUIT, &sig_quit) ≡ signal(3, pointer to handler)
 * 		glb_signals.exit = 130 ≡ the standard code indicating that a program 
 * 								 was interrupted by the SIGINT signal (Ctrl+C).
 * 		glb_signals.exit = 131 ≡ the standard code indicating that a program 
 * 								 was interrupted by the SIG	QUIT signal 
 * 								 (Ctrl+\).
 * 
 * @param minishell 			Pointer to the `t_minishell` structure that 
 * 								provides the current working directory prompt.
 * 
 * The function "sig_quit" is SIGQUIT signal handler (Ctrl+\).
 * 		- 	If `g_signals.pid` is non-zero, it sets `exit` to EX_SIGQUIT and 
 * 			outputs a newline, indicating that an external process received 
 * 			SIGQUIT.
 * 
 * @param status Signal status code (unused).
 * 
 * The function "sig_int" is SIGINT signal handler (Ctrl+C).
 * 		- 	If `g_signals.pid` is 0, this indicates that `minishell` is in 
 * 			prompt mode, so it outputs a newline, the custom prompt from 
 * 			`dupdirprompt`, and sets `exit` to 1.
 * 		- 	If `g_signals.pid` is non-zero, indicating an external process, it 
 * 			sets `exit` to EX_SIGINT and outputs a newline.
 * 
 * @param status Signal status code (unused).
 * 
 * The function "ft_init_struc_sig" initializes all members contained in the 
 * t_signal structure.
 * 
 * @param t_signal *signals 	Pointer to the `t_signal` structure containing 
 * 								the signals to be initialized. This structure 
 * 								has several fields related to signal handling 
 * 								such as SIGINT and SIGQUIT.
 * 
 * The function `ft_handle_eof` handles the scenario where an EOF (End Of File) 
 * is detected, typically when the user presses Ctrl+D. When EOF is 
 * encountered, the function prints "exit" and gracefully exits the `minishell`
 * program.
 *
 * @param char *line - The current input line being read. If NULL, it indicates
 *                     EOF (Ctrl+D) has been detected.
 *
 * 		Steps:
 * 			1. Check if the input line is NULL, which indicates the EOF 
 * 			   condition.
 * 			2. Print "exit" followed by a newline to notify the user that the 
 * 			   shell is terminating.
 * 			3. Exit the program with a status code of 0, indicating successful 
 * 			   termination.
 * 
 * 		Notes lines:
 * 			First line.  Print "exit" to indicate termination.
 * 			Second line. Exit the program with a success status.
 * 
 * 
 * 						*******************
 * 						NOTES ABOUT SIGNALS
 *	 					*******************
 * 
 * Normal exit codes: When a process is terminated normally (for example, using
 * exit(0) or exit(1)), the exit code is simply the value passed to exit().
 * 
 * Exit codes due to signals: When a process is terminated by a signal, the 
 * exit code is set to 128 + the signal number.
 * 
 * Why 128?
 * 
 * On Unix/Linux, exit codes for processes range from 0 to 255.
 * The numbers 0 to 127 are reserved for processes that terminate normally 
 * (with exit()), and the numbers 128 to 255 are used to indicate that a 
 * process was terminated by a signal.
 * 
 * 0000 0000 a 0111 1111 : Exit, Return
 * 1000 0000 a 1111 1111 : Signals
 * 
 * The number 128 acts as an indicator that the process was terminated by a 
 * signal, not by normal termination.
 * 
 * Examples: 130 ≡ exit for SIGINT (128 + 2) ≡ 1000 0010
 * 			 131 ≡ exit for SIGQUIT (128 + 3) ≡ 1000 0011
 * 
 * CONTROL + C -> SIGINT (Signal number 2)
 * CONTROL + \ -> SIGQUIT (Signal number 3)
 * 
 */

void	ft_handle_eof(char *line)
{
	if (!line)
	{
		ft_putstr_fd("exit\n", STDERR);
		exit (0);
	}
}

void	ft_init_struc_sig(t_signal *signals)
{
	signals->pid = 0;
	signals->sigint = 0;
	signals->sigquit = 0;
	signals->exit = 0;
	signals->start = 1;
}

static void	sig_int(int status)
{
	(void) status;

	if (g_signals.pid == 0)
	{
		ft_putstr_fd("\n", STDERR);
		ft_putstr_fd(g_signals.dupdirprompt, STDERR);
		//g_signals.exit = 1;
	}
	else
	{
		ft_putstr_fd("\n", STDERR);
		g_signals.exit = EX_SIGINT;
	}
	g_signals.sigint = 1;
}

static void	sig_quit(int status)
{
	(void) status;

	if (g_signals.pid != 0)
	{
		ft_putstr_fd("\n", STDERR);
		g_signals.exit = EX_SIGQUIT;
	}
	g_signals.sigquit = 1;
}

void	ft_init_signals(t_minishell *minishell)
{
	ft_dirprompt(minishell);
	if (g_signals.dupdirprompt)
		free(g_signals.dupdirprompt);
	g_signals.dupdirprompt = minishell->dirprompt;
	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
	ft_enable_print();
}
