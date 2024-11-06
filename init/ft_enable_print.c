/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enable_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-05 09:52:49 by rdel-olm          #+#    #+#             */
/*   Updated: 2024-11-05 09:52:49 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function `ft_enable_print` modifies the terminal attributes to enable
 * the display of control characters, such as `^C` when `Ctrl+C` is pressed.
 * This ensures that control characters are visible in the terminal when 
 * signals like `SIGINT` are triggered.
 *
 * 		Steps:
 * 			1. 	Retrieve the current terminal attributes using `tcgetattr`.
 * 			2. 	Modify the `c_lflag` field by setting the `ECHOCTL` flag, which 
 * 				enables the display of control characters in the terminal.
 * 			3. 	Apply the modified attributes immediately using `tcsetattr` 
 * 				with `TCSANOW` to ensure the change takes effect without delay.
 *
 * @note This function is useful when you want to restore the default terminal
 *       behavior of displaying control characters after they have been 
 *       disabled.
 *
 * @param void 	 This function does not take any parameters and modifies the 
 *               terminal settings directly.
 * 
 * 		Notes lines:
 * 			First line.		Retrieve the current settings of the terminal.
 * 			Second line.	Enable the ECHOCTL flag to display control 
 * 							characters like ^C.
 * 			Third line.		Apply the updated settings to the terminal. 
 * 
 */

void	ft_enable_print(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
