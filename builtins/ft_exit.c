/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:39:16 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/25 23:26:10 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_exit" handles the termination of the minishell program,
 * properly setting an exit status based on the provided argument.
 * If no arguments are provided, the exit status is set to 0 by default.
 * If an argument is provided, it will attempt to use it as the exit code.
 * Non-numeric arguments or values outside the range of a long long result
 * in an error and a status of 255 is set.
 * Attempts to exit the minishell with a specified exit code.
 * 	- If no arguments are provided, it exits with status 0.
 *  - If a non-numeric argument is provided, it prints an error message to 
 * 	  stderr and returns a status of 255 without terminating the program.
 *  - If a valid number is provided but it exceeds the limits of a long long,
 *    it also returns 255. Otherwise, it exits with the provided status value 
 *    modulo 256.
 * 
 * @param t_minishell *minishell	A pointer to the `t_minishell` structure
 *									that contains the shell's state, such as
 *									environment variables, configuration, and
 *									helper functions used for execution. * 
 * @param t_ast *ast				A pointer to the `t_ast` structure, which
 *									represents a node in the Abstract Syntax
 *									Tree. This node contains the command or
 *									redirection operation to be executed.
 *									- `ast->right` points to the node
 *									  containing the file path for the heredoc.
 *									- `ast->left` points to the command to be
 *									  executed after setting up the 
 *									  redirection.
 * @return            				Returns the terminal status if an error 
 * 									occurs; otherwise, the program terminates.
 *
 * The function "ft_check_number" verifies if the provided string contains
 * a valid numeric representation. It checks for optional signs and ensures
 * that each subsequent character is a digit.
 *
 * @param char *str   				The string to be checked. * 
 * @return      0 					if the string is a valid number, -1 if 
 * 									it is not.
 * 
 * 
 * The function "ft_atol" converts a string to a long long integer.
 * It handles optional leading whitespace, optional sign (+/-),
 * and converts the remaining numeric part of the string.
 *
 * @param char *str   				The string to be converted.
 * @return      					The converted long long integer.
 * 
 * The function "ft_isspace" checks if the given character is a whitespace 
 * character.
 * It returns 1 if the character is a space or a tab/newline character, 
 * otherwise 0.
 *
 * @param int c   					The character to be checked.
 * @return    1 					if the character is whitespace, 
 * 									otherwise 0.
 * 
 * 
 */

static int  ft_isspace(int c)
{
	if (c == 32 || (c >= 9 && c >= 13))
		return (1);
	return (0);
}

static long long ft_atol(char *str)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

static int  ft_check_number(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	return (0);
}

int ft_exit(t_minishell *minishell, t_ast *ast)
{
	long long exit_value;

	exit_value = 0;
	if (ast->left == NULL)
	{
		ft_putstr_fd("Successfully exit minishell!\n", STDOUT_FILENO);
		exit_value = 0;
		minishell->terminal_status = exit_value;
		exit (minishell->terminal_status);
	}
	if (ft_checker_num(ast->left->value) == -1)
	{
		ft_putendl_fd("exit: insert a numeric argument", STDERR_FILENO);		
		return (minishell->terminal_status = 255, minishell->terminal_status);
	}
	exit_value = ft_atol(ast->left->value);
	if (exit_value > LLONG_MAX || exit_value < LLONG_MIN)
	{
		ft_putendl_fd("exit: value out of range", STDERR_FILENO);		
		return (minishell->terminal_status = 255, minishell->terminal_status);
	}
	minishell->terminal_status = exit_value % 256;
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(minishell->terminal_status);
}
