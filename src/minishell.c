/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:33:21 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/10/29 20:19:35 by rdel-olm         ###   ########.fr       */
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
	// t_ast		*cmd_ast;

	(void)argc;
	(void)argv;
	if (argc != 1 || argv[1])
		ft_manage_err(YELLOW NUM_ARGV_ERR RESET);
	ft_init_struc_sig(&g_signals);
	ft_init_signals();
	ft_print_init();
	if (envp && argc == 1)
		minishell = ft_init_minishell(envp);
	else
		minishell = ft_init_minishell(minishell.envp);
	while (1)
	{
		ft_sync_envp(&minishell);
		minishell.line = readline(minishell.dirprompt);
		if (!minishell.line)
			break ;
		ft_tokenizer(&minishell);
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
		ft_free_tokens(minishell.tokens);
		minishell.tokens = NULL;
	}
	
	// while (!g_signals.exit)
	// {
	// 	cmd_ast = ft_tokenizer(&minishell);
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
	// }

	rl_clear_history();
	ft_free_minishell(&minishell);
	return (0);
}
