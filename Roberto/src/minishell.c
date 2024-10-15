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
 * @param int argc 		xxx
 * @param char **argv	xxx
 * @param char **envp	xxx
 * 
 */

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*minishell;

	(void)argc;
	(void)argv;
	if (argc != 1 || argv[1])
		ft_manage_err(YELLOW NUM_ARGV_ERR RESET);
	if (argc != 1 || envp == NULL || *envp == NULL)
		ft_manage_err(YELLOW ENV_ERR RESET);
	// t_envp *current; // para visualizar (Eliminar en definitivo)
	ft_init_struc_sig(&glb_signals);
	ft_init_signals();
	ft_print_init();
	minishell = ft_init_minishell(envp);
	if (!minishell)
		return (EXIT_FAILURE);
	//
	//
	// current = minishell->list_envp;
	// while (current) // para visualizar (Eliminar en definitivo)
	// {
	// 	printf("Variable: %s=%s\n", current->key, current->value);
	// 	current = current->next;
	// }
	//
	//
	// while (!glb_signals.exit)
	// {
	// 	t_ast *cmd_ast = ft_parse(minishell);
	// 	if (cmd_ast)
	// 		ft_is_builtin(cmd_ast);
	// }
	clear_history();
	return (0);
}
