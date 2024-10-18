/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:11:14 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/10/15 23:29:22 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_init_signals" initializes the handler for each signal.
 * 		signal(SIGINT, &sig_int) ≡ signal(2, pointer to handler)
 * 		signal(SIGQUIT, &sig_quit) ≡ signal(3, pointer to handler)
 * 		glb_signals.exit = 130 ≡ the standard code indicating that a program 
 * 								 was interrupted by the SIGINT signal (Ctrl+C).
 * 		glb_signals.exit = 131 ≡ the standard code indicating that a program 
 * 								 was interrupted by the SIG	QUIT signal 
 * 								 (Ctrl+\).
 * 
 * The function "sig_quit" is SIGQUIT signal handler.
 * 
 * The function "sig_int" is SIGINT signal handler.
 * 
 * The function "ft_init_struc_sig" initializes all members contained in the 
 * t_signal structure.
 * 
 * @param t_signal *signals 	Pointer to the `t_signal` structure containing 
 * 								the signals to be initialized. This structure 
 * 								has several fields related to signal handling 
 * 								such as SIGINT and SIGQUIT.
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

void	ft_init_struc_sig(t_signal *signals)
{
	signals->pid = 0;
	signals->sigint = 0;
	signals->sigquit = 0;
	signals->exit = 0;
}

static void	sig_int(int status)
{
	(void) status;

	if (g_signals.pid == 0)
	{
		ft_putstr_fd("\n", STDERR);
		ft_putstr_fd(PROMPT, STDERR);
		g_signals.exit = 1;
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

void	ft_init_signals(void)
{
	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
}
