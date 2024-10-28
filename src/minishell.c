/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:33:21 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/10/28 12:21:23 by pabromer         ###   ########.fr       */
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
	}
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
