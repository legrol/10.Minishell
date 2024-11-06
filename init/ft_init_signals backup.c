/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_signals backup.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-06 06:55:05 by rdel-olm          #+#    #+#             */
/*   Updated: 2024-11-06 06:55:05 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
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

// static void	sig_int(int status, t_minishell *minishell)
// {
// 	(void) status;

// 	if (g_signals.pid == 0)
// 	{
// 		ft_putstr_fd("\n", STDERR);
// 		if (minishell != NULL)
// 		{
// 			ft_dirprompt(minishell);
// 			ft_putstr_fd(minishell->dirprompt, STDERR);
// 		}
// 		g_signals.exit = 1;
// 	}
// 	else
// 	{
// 		ft_putstr_fd("\n", STDERR);
// 		g_signals.exit = EX_SIGINT;
// 	}
// 	g_signals.sigint = 1;
// }

// static void	sig_int(int status)
// {
// 	(void) status;

// 	if (g_signals.pid == 0)
// 	{
// 		ft_putstr_fd("\n", STDERR);
// 		g_signals.exit = 1;
// 	}
// 	else
// 	{
// 		ft_putstr_fd("\n", STDERR);
// 		g_signals.exit = EX_SIGINT;
// 	}
// 	g_signals.sigint = 1;
// }

static t_minishell	*get_minishell_instance(void)
{
	static t_minishell	*instance;

	instance = NULL;
	return (instance);
}

static void	set_minishell_instance(t_minishell *minishell)
{
	static t_minishell	**instance;

	instance = &minishell;
}

static void	sig_int(int status)
{
	t_minishell	*minishell;

	(void) status;
	minishell = get_minishell_instance();
	if (g_signals.pid == 0 && minishell != NULL)
	{
		ft_putstr_fd("\n", STDERR);
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_dirprompt(minishell);
		ft_putstr_fd(minishell->dirprompt, STDERR);
		rl_redisplay();
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
// void	ft_init_signals(t_minishell *minishell)
// {
// 	// signal(SIGINT, &sig_int);
// 	signal(SIGQUIT, &sig_quit);
// 	ft_enable_print();
// }

// void	ft_init_signals(t_minishell *minishell)
// {
// 	struct sigaction	sa_int;
// 	struct sigaction	sa_quit;

// 	// Configurar el manejador para SIGINT
// 	sa_int.sa_handler = (__sighandler_t)(void (*)(int))sig_int;
// 	sigemptyset(&sa_int.sa_mask);
// 	sa_int.sa_flags = SA_RESTART;
// 	sigaction(SIGINT, &sa_int, NULL);

// 	sig_int(0, minishell);

// 	sa_quit.sa_handler = &sig_quit;
// 	sigemptyset(&sa_quit.sa_mask);
// 	sa_quit.sa_flags = SA_RESTART;
// 	sigaction(SIGQUIT, &sa_quit, NULL);


// 	// signal(SIGQUIT, &sig_quit);
// 	ft_enable_print();
// }


// void	ft_init_signals(t_minishell *minishell)
// {
// 	struct sigaction	sa_int;
// 	struct sigaction	sa_quit;

// 	(void) minishell;
// 	// Configurar el manejador para SIGINT
// 	sa_int.sa_handler = &sig_int;
// 	sigemptyset(&sa_int.sa_mask);
// 	sa_int.sa_flags = SA_RESTART;
// 	sigaction(SIGINT, &sa_int, NULL);

// 	// Configurar el manejador para SIGQUIT
// 	sa_quit.sa_handler = &sig_quit;
// 	sigemptyset(&sa_quit.sa_mask);
// 	sa_quit.sa_flags = SA_RESTART;
// 	sigaction(SIGQUIT, &sa_quit, NULL);

// 	ft_enable_print();
// }

void sig_int_wrapper(int status)
{
	t_minishell	*minishell;

	(void)status;
	minishell = get_minishell_instance();
	if (g_signals.pid == 0 && minishell != NULL)
	{
		ft_putstr_fd("\n", STDERR);
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_dirprompt(minishell);
		ft_putstr_fd(minishell->dirprompt, STDERR);
		rl_redisplay();
		g_signals.exit = 1;
	}
	else
	{
		ft_putstr_fd("\n", STDERR);
		g_signals.exit = EX_SIGINT;
	}
	g_signals.sigint = 1;
}

void	sig_quit_wrapper(int status)
{
	(void)status;

	if (g_signals.pid != 0)
	{
		ft_putstr_fd("\n", STDERR);
		g_signals.exit = EX_SIGQUIT;
	}
	g_signals.sigquit = 1;
}

void	ft_register_signals(t_minishell *minishell)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	set_minishell_instance(minishell);

	sa_int.sa_handler = &sig_int_wrapper;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);

	sa_quit.sa_handler = &sig_quit_wrapper;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);

	ft_enable_print();
}
