/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:33:21 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/06 15:09:13 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The "main" function of minishell program.
 * 
 * @param int argc 			Number of arguments the program receives from the 
 * 							command line. This is expected to be 1 (just the 
 * 							program name), otherwise an error message is 
 * 							displayed.
 * @param char **argv		String array containing the arguments passed to the 
 * 							program. This program does not take any additional 
 * 							arguments beyond the program name, and passing more
 * 							than that results in an error.
 * @param char **envp		String array containing the system environment 
 * 							variables. These are needed for initializing the 
 * 							`t_minishell` structure and managing the shell 
 * 							environment.
 * 
 * NOTE: g_signals.start 	Integer what indicates the minishell was 
 * 							initialized.
 * 
 * The function "ft_init_envp" initializes the envp inside the minishell 
 * structure. This function takes an array of environment variables (`envp`)
 * and duplicates each entry into the `minishell->envp` array within the 
 * `t_minishell` structure. The function calculates the number of entries
 * in `envp`, allocates memory for each variable, and duplicates them 
 * individually, adding a NULL pointer at the end. 
 * 
 * @param t_minishell *minishell	Pointer to the main minishell structure
 *                                  where the environment variables will 
 *                                  be stored.
 * @param char **envp				Array of environment variables passed
 *                                  to the program by the operating system.
 *  
 * NOTE: t_signal g_signals			Is a global variable that handles input 
 * 									signals. It must be accessible from any 
 * 									area of ​​the minishell program, hence its
 * 									global nature.
 * 
 */

t_signal g_signals;

static int	ft_start_init_envp(t_minishell *minishell, char **envp)
{
	int		i;

	i = 0;
	if (!envp)
		return (-1);
	while (envp[i])
		i++;
	minishell->envp = (char **)malloc((i + 1) * sizeof(char *));
	if (!minishell->envp)
		return (-1);
	return (0);
}

static void	ft_init_envp(t_minishell *minishell, char **envp)
{
	int		i;

	i = 0;
	if (ft_start_init_envp(minishell, envp))
		return ;
	i = 0;
	while (envp[i])
	{
		minishell->envp[i] = ft_strdup(envp[i]);
		if (!minishell->envp[i])
		{
			while (i > 0)
			{
				free(minishell->envp[--i]);
			}
			free(minishell->envp);
			minishell->envp = NULL;
			return ;
		}
		i++;
	}
	minishell->dirprompt = NULL;
	minishell->envp[i] = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;
	int			i;
	t_ast		*ast;
	t_ast		*temp;
	t_ast		*ltemp;

	i = 0;
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
			ft_init_signals(&minishell);
			ft_init_minishell(&minishell);
		}
		minishell.line = readline(minishell.dirprompt);
		ft_handle_eof(minishell.line);
		if (!minishell.line || ft_checker_quotes_unclosed(&minishell))
		{
			if (minishell.line)
				free(minishell.line);
			minishell.line = NULL;
			continue ;
		}
		ft_tokenizer(&minishell);
		ast = ft_ast(&minishell);
		ft_printf("AQUI ESTOY\n");
		temp = ast;
		while (ast)
		{
			ft_printf("Node: %s\n", ast->value);
			ltemp = ast;
			while(ast->left)
			{
				ast = ast->left;
				ft_printf("Left: %s\n", ast->value);
			}
			ast = ltemp;
			ast = ast->right;
		}
		ast = temp;
		/*while (ast)
		{
			if (ft_strcmp(ast->value, "cd") == 0)
				ft_cd(&minishell, ast);
			else if (ft_strcmp(ast->value, "env") == 0)
				ft_env(&minishell);
			else if (ft_strcmp(ast->value, "pwd") == 0)
				ft_pwd();
			else if (ft_strcmp(ast->value, "echo") == 0)
				ft_echo(&minishell, ast);
			else if (ft_strcmp(ast->value, "export") == 0)
				ft_export(&minishell, ast);
			else if (ft_strcmp(ast->value, "unset") == 0)
				ft_unset(&minishell, ast);
			else if (ft_strcmp(ast->value, "exit") == 0)
				i = 1;
			else
				ft_cmdexe(&minishell);
			ast = ast->right;
		}*/
		ast = temp;
		ft_free_ast(ast);
		free(minishell.line);
		minishell.line = NULL;
		ft_free_tokens(minishell.tokens);
		minishell.tokens = NULL;
		if (i == 1)
			break ;
	}
	rl_clear_history();
	ft_free_minishell(&minishell);
	return (0);
}




/*void ft_print_ast(t_ast *node)
{
    if (!node)
        return;
    if (node->type == TOKEN_COMMAND)
        ft_printf("Comando: %s\n", node->value);
    else if (node->type == TOKEN_ARGUMENT)
        ft_printf("Argumento: %s\n", node->value);
    else if (node->type == TOKEN_PIPE)
        ft_printf("Operador (Pipe): %s\n", node->value);
    else if (node->type == TOKEN_REDIRECT_IN)
        ft_printf("Redirección In: %s\n", node->value);
    else if (node->type == TOKEN_REDIRECT_OUT)
        ft_printf("Redirección Out: %s\n", node->value);
    else if (node->type == TOKEN_REDIRECT_APPEND)
        ft_printf("Redirección Append: %s\n", node->value);
    else if (node->type == TOKEN_REDIRECT_HEREDOC)
        ft_printf("Redirección Heredoc: %s\n", node->value);
    if (node->left)
    {
        ft_printf("  └ Left: ");
        ft_print_ast(node->left);
    }
    if (node->right)
    {
        ft_printf("  └ Right: ");
        ft_print_ast(node->right);
    }
}*/
