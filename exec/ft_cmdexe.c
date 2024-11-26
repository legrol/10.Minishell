/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdexe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:22:00 by pabromer          #+#    #+#             */
/*   Updated: 2024/11/26 10:46:29 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_cmdexe" executes a command in a child process. It creates 
 * an argument array and a command path, forks a new process, and calls 
 * `execve` to execute the command in the child process.
 * 
 * - The parent process waits for the child process to finish and updates the 
 *   shell's exit status.
 * - If `fork` or `execve` fails, an error message is printed, and the shell 
 *   exits with an error code.
 * 
 * @param t_minishell *minishell	A pointer to the shell's state structure, 
 *									which contains environment variables and 
 *									execution status.
 * 
 * @param t_ast *ast				A pointer to the `t_ast` structure 
 * 									containing the command and its arguments.
 * 
 * @return void						This function does not return a value.
 * 
 * The function "ft_arg_maker" creates an array of arguments from an `ast` 
 * linked list. It traverses the `ast` to count the number of arguments, 
 * allocates memory for the argument array, and duplicates each value from 
 * the `ast` into the array.
 * 
 * - The last element of the array is set to `NULL` to terminate the argument 
 * list.
 * - Returns `NULL` if memory allocation fails.
 * 
 * @param t_ast *ast	A pointer to the `t_ast` structure containing the 
 *						command and its arguments.
 * 
 * @return char**		A dynamically allocated array of strings representing 
 *						the arguments, or `NULL` if memory allocation fails.
 * 
 * The function "ft_cmd_maker" generates the full executable path for a 
 * command using the paths available in the shell's `PATH` environment 
 * variable. It calls `ft_cmd_action` to find the executable path.
 * 
 * @param t_minishell *minishell	A pointer to the shell's state structure, 
 *									which contains the environment variables.
 * 
 * @param t_ast *ast				A pointer to the `t_ast` structure 
 *									representing the command and its arguments.
 * 
 * @return char*					A dynamically allocated string containing 
 *									the full path to the executable command 
 *									or `NULL` if the command is not found.
 * 
 * The function "ft_cmd_action" searches for a command in the directories 
 * specified by the `path` array. It trims unnecessary characters from the 
 * command name, combines it with each directory in the `path`, and checks 
 * if the resulting path is executable using `access`.
 * 
 * - If the command is found, it returns the full executable path.
 * - If the command is not found in the `path`, it checks if the `arg` is 
 *   directly executable and returns it if valid.
 * - Returns `NULL` if the command is not executable.
 * 
 * @param char **path	A NULL-terminated array of strings representing the 
 *						paths to search for the command.
 * 
 * @param char *arg		The command to be searched for.
 * 
 * @return char*		A dynamically allocated string containing the full path 
 *						to the executable command or `NULL` if the command is 
 *						not found.
 * 
 */

/**
 * Buscar y ejecutar el ejecutable correcto (basado en la variable PATH o 
 * mediante el uso de rutas relativas o absolutas). FALTA EL USO DE VARIABLES
 * RELATIVAS O ABSOLUTAS
 * 
*/

#include "../includes/minishell.h"

static void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

char	*ft_cmd_action(char **path, char *arg)
{
	int		i;
	char	*cmd;
	char	*temp;

	temp = ft_strtrim(arg, ".");
	i = 0;
	while (path[i])
	{
		cmd = ft_strjoin(path[i], temp);
		if (access(cmd, X_OK) == 0)
		{
			free(temp);
			return (cmd);
		}
		free (cmd);
		cmd = NULL;
		i++;
	}
	free(temp);
	if (access(arg, X_OK) == 0)
		return (free_path(path), ft_strdup(arg));
	free_path(path);
	return (NULL);
}

char	*ft_cmd_maker(t_minishell *minishell, t_ast *ast)
{
	char	**path;
	char	*cmd;

	path = ft_path(minishell);
	cmd = ft_cmd_action(path, ast->value);
	return (cmd);
}

char	**ft_arg_maker(t_ast *ast)
{
	char	**arg;
	t_ast	*temp;
	int		i;

	i = 0;
	temp = ast;
	while (ast)
	{
		i++;
		ast = ast->left;
	}
	ast = temp;
	arg = (char **)malloc((i + 1) * sizeof(char *));
	if (!arg)
		return (NULL);
	i = 0;
	while (ast)
	{
		arg[i] = ft_strdup(ast->value);
		ast = ast->left;
		i++;
	}
	arg[i] = NULL;
	ast = temp;
	return (arg);
}

void	ft_cmdexe(t_minishell *minishell, t_ast *ast)
{
	char	**arg;
	char	*cmd;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork fallo");
		exit (EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		arg = ft_arg_maker(ast);
		cmd = ft_cmd_maker(minishell, ast);
		execve(cmd, arg, minishell->envp);
		perror("execve cmd2:");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		//ft_free_ast(ast);
		minishell->exit = WEXITSTATUS(status);
	}
}
