/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 09:35:55 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/10/03 19:03:20 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ============================================================================
// Libraries
// ============================================================================
# include <unistd.h>		// for write...
# include <stdlib.h>		// for typedef, malloc...
# include <math.h>			// for PI, etc.
# include <fcntl.h>			// for open, O_RDONLY, etc.
# include <stdio.h>			// for printf...
# include <stdbool.h>		// for booleans...
# include <signal.h>		// for XXXXX
# include <limits.h>		// for XXXXX

// ============================================================================
// Access to my libraries
// ============================================================================
# include "colors.h"
# include "examft.h"
# include "ft_printf.h"
# include "get_next_line_bonus.h"
# include "get_next_line.h"
# include "libft.h"
# include "ft_macros.h"

// ============================================================================
// Structures
// ============================================================================
typedef struct s_minishell
{
	int	xxx;

}	t_minishell;

// ============================================================================
// Management errors
// ============================================================================
void	ft_manage_err(const char *err);

// ============================================================================
// Initialization functions
// ============================================================================
void	ft_minishell(t_minishell *mshll, char **envp);

// ============================================================================
// Initialization functions
// ============================================================================
void	ft_print_init(void);

// ============================================================================
// Global variable
// ============================================================================
// extern	t_minishell gl_mshll;

# endif
