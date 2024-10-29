/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:33:21 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/10/29 17:11:53 by pabromer         ###   ########.fr       */
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
 * @param int g_signals.start Integer what indicates the minishell was initialized.
 * 
 * ft_init_envp			Function what initializes the envp inside the 
 * 						minishell structure.		
 *  
 */

t_signal g_signals;

static void	ft_init_envp(t_minishell *minishell, char **envp)
{
	int		i;

	i = 0;
	if (!envp)
			return ;
	while (envp[i])
		i++;
	minishell->envp = (char **)malloc((i + 1) * sizeof(char *));
	if (!minishell->envp)
		return ;
	i = 0;
	while (envp[i])
	{
		minishell->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	minishell->envp[i] = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;
	int			i;
	t_ast		*ast;
	t_ast		*temp;
	//char *temp;

	(void)argc;
	(void)argv;
	if (argc != 1 || argv[1])
		ft_manage_err(YELLOW NUM_ARGV_ERR RESET);
	ft_print_init();
	ft_init_envp(&minishell, envp);
	while (1)
	{
		if (g_signals.start != 1)
		{
			ft_init_struc_sig(&g_signals);
			ft_init_signals();
			ft_init_minishell(&minishell);
		}
		minishell.line = readline(minishell.dirprompt);
		if (ft_strcmp(minishell.line, "") == 0)
			printf("HOLA");
		ft_tokenizer(&minishell);
		ast = ft_ast(&minishell);
		temp = ast;
		while (ast)
		{
			printf("%s %i\n", ast->value, ast->type);
			if (ft_strcmp(ast->value, "cd") == 0)
				ft_cd(&minishell, ast);
			else if (ft_strcmp(ast->value, "env") == 0)
				ft_env(&minishell);
			else if (ft_strcmp(ast->value, "pwd") == 0)
				ft_pwd(&minishell);
			else if (ft_strcmp(ast->value, "echo") == 0)
				ft_echo(&minishell);
			else if (ft_strcmp(ast->value, "export") == 0)
				ft_export(&minishell);
			else if (ft_strcmp(ast->value, "exit") == 0)
				i = 1;
			else
				ft_cmdexe(&minishell);
			ast = ast->right;
		}
		
		ast = temp;
		printf("\n");
		free(minishell.line);
		if (i == 1)
			break;
	}
	rl_clear_history();
	i = 0;
	while (minishell.envp[i])
	{
		free(minishell.envp[i]);
		i++;
	}
	free_tokens(minishell.tokens);
	// free_envp_list(minishell.list_envp);
	//free(minishell.line);
	free(minishell.envp);
	free(minishell.dirprompt);
	free(minishell.list_envp->key);
	free(minishell.list_envp->value);
	free(minishell.list_envp);
	return (0);
}
