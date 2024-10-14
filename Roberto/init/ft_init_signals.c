/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:11:14 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/10/14 21:28:06 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_init_signal" xxx
 * 
 * The function "sig_quit" xxx
 * 
 * @param xxx
 * 
 * The function "sig_int" xxx
 * 
 * @param xxx
 * 
 * The function "ft_init_struc_sig" xxx
 * 
 * @param t_signal *signals xxx
 * 
 * 
 * *****NOTES ABOUT SIGNALS***** 
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
 * The number 128 acts as an indicator that the process was terminated by a 
 * signal, not by normal termination.
 * 
 * CONTROL + C -> SIGINT (Signal 2)
 * CONTROL + \ -> SIGQUIT (Signal 3)
 * 
 */

void	ft_init_struc_sig(t_signal *signals)
{
	signals->pid = 0;
	signals->sigint = 0;
	signals->sigquit = 0;
	signals->exit = 0;
}

static void sig_int()
{


}

static void sig_quit()
{

	
}

void	ft_init_signal(void)
{
	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
}
