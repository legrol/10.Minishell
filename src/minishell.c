/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:33:21 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/10/16 15:45:46 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The main function of minishell.
 * 
 * @param int argc 		Number of arguments the program receives from the 
 * 						command line. This is expected to be 1 (just the 
 * 						program name), otherwise an error message is 
 * 						displayed.
 * @param char **argv	String array containing the arguments passed to the 
 * 						program. This program does not take any additional 
 * 						arguments beyond the program name, and passing more 
 * 						than that results in an error.
 * @param char **envp	String array containing the system environment 
 * 						variables. These are needed for initializing the 
 * 						`t_minishell` structure and managing the shell 
 * 						environment.
 *  
 */

t_signal glb_signals;

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*minishell;

	(void)argc;
	(void)argv;
	if (argc != 1 || argv[1])
		ft_manage_err(YELLOW NUM_ARGV_ERR RESET);
	if (argc != 1 || envp == NULL || *envp == NULL)
		ft_manage_err(YELLOW ENV_ERR RESET);
	//t_envp *current; // para visualizar (Eliminar en definitivo)
	ft_init_struc_sig(&glb_signals);
	ft_init_signals();
	ft_print_init();
	minishell = ft_init_minishell(envp);
	if (!minishell)
		return (EXIT_FAILURE);
	
	
	// current = minishell->list_envp;
	// while (current) // para visualizar (Eliminar en definitivo)
	// {
	// 	printf("Variable: %s=%s\n", current->key, current->value);
	// 	current = current->next;
	// }
	
	while (1)
	{
		minishell->line = readline(minishell->dirprompt);
		if (ft_strnstr(minishell->line, "cd", ft_strlen(minishell->line)))
			ft_cd(minishell);
		if (ft_strnstr(minishell->line, "env", ft_strlen(minishell->line)))
			ft_env(minishell);
		if (ft_strnstr(minishell->line, "pwd", ft_strlen(minishell->line)))
			ft_pwd(minishell);
	}
	
	// while (!glb_signals.exit)
	// {
	// 	t_ast *cmd_ast = ft_parse(minishell);
	// 	if (cmd_ast)
	// 		ft_is_builtin(cmd_ast);
	// }
	free(minishell);
	rl_clear_history();
	return (minishell->exit);
}
