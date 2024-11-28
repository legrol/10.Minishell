/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-28 08:52:45 by rdel-olm          #+#    #+#             */
/*   Updated: 2024-11-28 08:52:45 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_exit_check_limits" validates the provided argument for the
 * "exit" command, ensuring it does not exceed the range of a long long integer.
 * If the argument is invalid, it prints an error message and exits the program
 * with a status of 255.
 *
 * @param char *arg                 The argument to validate.
 * @param t_minishell *minishell    A pointer to the `t_minishell` structure
 *                                  containing the shell's state.
 * @return void                     Does not return, exits the program.
 * 
 * The function "ft_exit_too_many_arguments" handles the case where the "exit"
 * command is called with more than one argument. It prints an error message
 * and does not terminate the program, returning a status of 1 instead.
 *
 * @param t_minishell *minishell    A pointer to the `t_minishell` structure
 *                                  containing the shell's state.
 * @return int                      Returns 1 to indicate an error.
 * 
 * The function "ft_exit_invalid_argument" validates the provided argument for
 * the "exit" command. If the argument is not numeric, it prints an error 
 * message and exits the program with a status of 255.
 *
 * @param char *arg                 The argument to validate.
 * @param t_minishell *minishell    A pointer to the `t_minishell` structure
 *                                  containing the shell's state.
 * @return void                     Does not return, exits the program.
 * 
 * The function "ft_exit_no_arguments" handles the case where the "exit" command
 * is called without arguments. It terminates the program with a status of 0.
 *
 * @param t_minishell *minishell    A pointer to the `t_minishell` structure
 *                                  containing the shell's state.
 * @return void                     Does not return, exits the program. 
 * 
 * The function "ft_compare_to_limits" validates the length of a string
 * and ensures it does not exceed the range of a long long integer.
 *
 * @param char *str					The string to validate.
 * @return int						0 if the string is valid, -1 otherwise.
 * 
 */

int	ft_compare_to_limits(char *str)
{
	int	len;

	len = strlen(str);
	if ((len > MAX_NEG && str[0] == '-') || (len > MAX_DIGITS && str[0] != '-'))
		return (-1);
	if (ft_str_longcheck(str) == -1)
		return (-1);
	return (0);
}

void	ft_exit_no_arguments(t_minishell *minishell)
{
	ft_putstr_fd("Successfully exit minishell!\n", STDOUT_FILENO);
	minishell->terminal_status = 0;
	exit(minishell->terminal_status);
}

void	ft_exit_invalid_argument(char *arg, t_minishell *minishell)
{
	ft_printf("exit\n");
	ft_putstr_fd("exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	minishell->terminal_status = 255;
	exit(minishell->terminal_status);
}

int	ft_exit_too_many_arguments(t_minishell *minishell)
{
	ft_printf("exit\n");
	ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
	return (minishell->terminal_status = 1);
}

void	ft_exit_check_limits(char *arg, t_minishell *minishell)
{
	if (ft_compare_to_limits(arg) == -1)
	{
		ft_printf("exit\n");
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		minishell->terminal_status = 255;
		exit(minishell->terminal_status);
	}
}
