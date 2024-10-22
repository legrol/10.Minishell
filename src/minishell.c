/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:33:21 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/10/21 12:43:05 by pabromer         ###   ########.fr       */
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

t_signal g_signals;

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;
	int			i;
	t_ast		*cmd_ast;

	(void)argc;
	(void)argv;
	if (argc != 1 || argv[1])
		ft_manage_err(YELLOW NUM_ARGV_ERR RESET);
	//t_envp *current; // para visualizar (Eliminar en definitivo)
	ft_init_struc_sig(&g_signals);
	ft_init_signals();
	ft_print_init();
	if (envp && argc == 1)
		minishell = ft_init_minishell(envp);
	else
		minishell = ft_init_minishell(minishell.envp);
	/*if (!minishell)
		return (EXIT_FAILURE);*/
	// current = minishell.list_envp;
	// while (current) // para visualizar (Eliminar en definitivo)
	// {
	// 	printf("Variable: %s=%s\n", current.key, current.value);
	// 	current = current.next;
	// }
	
	while (1)
	{
		ft_sync_envp(&minishell);
		minishell.line = readline(minishell.dirprompt);
		if (ft_strnstr(minishell.line, "cd", ft_strlen("cd")))
			ft_cd(&minishell);
		else if (ft_strnstr(minishell.line, "env", ft_strlen("env")))
			ft_env(&minishell);
		else if (ft_strnstr(minishell.line, "pwd", ft_strlen("pwd")))
			ft_pwd(&minishell);
		else if (ft_strnstr(minishell.line, "echo", ft_strlen("echo")))
			ft_echo(&minishell);
		else if (ft_strnstr(minishell.line, "export", ft_strlen("export")))
			ft_export(&minishell);
		else if (ft_strnstr(minishell.line, "exit", ft_strlen("exit")))
			break ;
		else
			ft_cmdexe(&minishell);
		free(minishell.line);
	}
	while (!g_signals.exit)
	{
		cmd_ast = ft_tokenizer(&minishell);
		// if (cmd_ast->value) {
		// 		char *result = ft_find_cmd_path(cmd_ast, minishell);
		// 		if (result) {
		// 			ft_printf("Comando ejecutable encontrado: %s\n", result);
		// 			free(result); // Liberar la memoria después de usar
		// 		} else {
		// 			ft_printf("Comando no encontrado: %s\n", cmd_ast->value);
		// 		}
		// 	}
		// ft_is_builtin(cmd_ast, minishell); 
	}
	//free(&minishell);
	rl_clear_history();
	i = 0;
	while (minishell.envp[i])
	{
		free(minishell.envp[i]);
		i++;
	}
	free(minishell.line);
	free(minishell.envp);
	free(minishell.dirprompt);
	free(minishell.list_envp->key);
	free(minishell.list_envp->value);
	free(minishell.list_envp);
	return (0);
}
