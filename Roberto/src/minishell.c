/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:33:21 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/10/14 21:16:59 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The main function of minishell xxx.
 * 
 * @param xxxx
 * 
 */

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	if (argc != 1 || argv[1])
		ft_manage_err(YELLOW NUM_ARGV_ERR RESET);
	if (argc != 1 || envp == NULL || *envp == NULL)
		ft_manage_err(YELLOW ENV_ERR RESET);
	t_minishell *minishell;
	//t_envp *current; // para visualizar (Eliminar en definitivo)
	ft_init_struc_sig(&glb_signals);
	ft_init_signals();
	
	
	ft_print_init();
	
	
	
	ft_init_minishell();


}

// int main()
// {
// 	ft_print_init();
// }
