/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:39:16 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/26 22:21:10 by rdel-olm         ###   ########.fr       */
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
 * The function "ft_str_longcheck" compares the input string to LLONG_MAX
 * or LLONG_MIN based on its sign, ensuring it is within the valid range
 * of a long long integer.
 *
 * @param char *str					The string to be compared.
 * @return int						0 if the string is within limits, -1 if it
 * 									exceeds the range.
 * 
 * The function "ft_check_number" verifies if the provided string contains
 * a valid numeric representation. It checks for optional signs and ensures
 * that each subsequent character is a digit.
 *
 * @param char *str   				The string to be checked. * 
 * @return      0 					if the string is a valid number, -1 if 
 * 									it is not. * 
 * 
 * The function "ft_atol" converts a string to a long long integer.
 * It handles optional leading whitespace, optional sign (+/-),
 * and converts the remaining numeric part of the string.
 *
 * @param char *str   				The string to be converted.
 * @return      					The converted long long integer.
 *  
 */

static long long	ft_atol(char *str)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
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

static int	ft_checker_number(char *str)
{
	int	i;

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

int	ft_str_longcheck(char *str)
{
	int	s;
	int	i;

	s = 0;
	if (str[0] == '-')
		s = -1;
	if (s == -1)
		i = ft_strcmp(LLONGMIN, str);
	else
		i = ft_strcmp(LLONGMAX, str);
	if (i < 0)
		return (-1);
	return (0);
}

int	ft_exit(t_minishell *minishell, t_ast *ast)
{
	long long	exit_value;

	if (ast->left == NULL)
		ft_exit_no_arguments(minishell);
	if (ft_checker_number(ast->left->value) == -1)
		ft_exit_invalid_argument(ast->left->value, minishell);
	if (ast->left->left != NULL)
		return (ft_exit_too_many_arguments(minishell));
	ft_exit_check_limits(ast->left->value, minishell);
	exit_value = ft_atol(ast->left->value);
	minishell->terminal_status = exit_value % 256;
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(minishell->terminal_status);
}
