/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-15 06:23:12 by rdel-olm          #+#    #+#             */
/*   Updated: 2024-10-15 06:23:12 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_print_init" xxx
 * 
 * 
 */

void	ft_print_init(void)
{
	ft_printf(RED "  ___  ___ __                   __            __ __   \
	  \n");
	ft_printf(RED " |   \\/   (__)        __       |**|          |**|**| \
	  \n");
	ft_printf(RED " |  \\  /  |__ __  __ (__) _____|**|__    ____|**|**| \
	  \n");
	ft_printf(YELLOW " |  |\\/|  |  |  '_  \\|  |/   __|** _**\\ /*_**|**|**|\
	  \n");
	ft_printf(YELLOW " |  |  |  |  |  | |  |  |\\__  \\|**| |**|***__|**|**|\
	    \n");
	ft_printf(RED " |  |  |  |  |  | |  |  | __|  |**| |**|**\\__|**|**| \
	   \n");
	ft_printf(RED " |__|  |__|__|__| |__|__|\\____/|**| |**|\\****|**|**| \
	   \n\n");
	ft_printf(RED"Welcome to "BDYELLOW"Minishell, "RED"project by " GREEN \
	"pabromer " RED "and " GREEN "rdel-olm\n");
}
