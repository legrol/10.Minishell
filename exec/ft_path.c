/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:41:46 by pabromer          #+#    #+#             */
/*   Updated: 2024/11/26 16:56:42 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_path" retrieves the `PATH` environment variable, splits 
 * it into an array of directory paths, and appends the current working 
 * directory to the array. If the `PATH` variable is not set, it calls 
 * "ft_no_path" to handle this scenario.
 * 
 * - Uses `ft_find_dir` to find the value of `PATH` in the environment 
 *   variables.
 * - If `PATH` is not set, it returns the result of `ft_no_path`.
 * - Otherwise:
 *   - Splits the `PATH` variable into directories using `ft_split`.
 *   - Appends `/` to each directory path to facilitate command resolution.
 *   - Adds the current working directory as the final entry in the array.
 * - Frees intermediate memory allocations, including the original split array.
 * - Exits the program with `EXIT_FAILURE` if memory allocation fails.
 * 
 * @param t_minishell *minishell	A pointer to the shell's state structure, 
 *									used to retrieve the environment variables.
 * 
 * @return char**					A dynamically allocated array of strings 
 *									representing the directories in the `PATH` 
 *									variable, with each path ending in `/`.
 * 
 * The function "ft_no_path" handles cases where the `PATH` environment 
 * variable is not set. It returns a single-element array containing the 
 * current working directory, allowing commands to be resolved relative to 
 * the current directory.
 * 
 * - Allocates memory for the array.
 * - Uses `getcwd` to retrieve the current working directory.
 * - Sets the second element of the array to `NULL` to indicate termination.
 * - Exits the program with `EXIT_FAILURE` if memory allocation fails.
 * 
 * @return char**			A dynamically allocated array containing the 
 *							current working directory.
 * 
 * The function "p_mallocsize" calculates the number of substrings (delimited 
 * by a specific character `c`) in a given string `s`. This is used to 
 * determine the amount of memory needed to split the string.
 * 
 * - Iterates through the string and counts occurrences of `c` that are 
 *   preceded by a non-`c` character.
 * - If the string does not start with the delimiter, it includes the last 
 *   substring in the count.
 * 
 * @param char const *s		The input string to analyze.
 * @param char c			The delimiter character used to split the string.
 * 
 * @return unsigned int		The number of substrings in the input string.
 * 
 */

static unsigned int	p_mallocsize(char const *s, char c)
{
	int	ms;
	int	i;

	i = 0;
	ms = 0;
	if (s[0] == c)
		i++;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i - 1] != c)
			ms++;
		i++;
	}
	if (s[i - 1] != c)
		ms++;
	return (ms);
}

static char	**ft_no_path(void)
{
	char	**split_path;
	char	cwd[1024];

	split_path = (char **)malloc(2 * sizeof(char *));
	if (!split_path)
		exit(EXIT_FAILURE);
	split_path[0] = getcwd(cwd, sizeof(cwd));
	split_path[1] = NULL;
	return (split_path);
}

char	**ft_path(t_minishell *minishell)
{
	int		i;
	char	**split_path;
	char	**cp_split_path;
	char	*str;

	str = ft_find_dir(minishell, "PATH");
	if (!str)
		return (ft_no_path());
	cp_split_path = ft_split(str, ':');
	split_path = (char **)malloc((2 + p_mallocsize(str, ':')) * \
				sizeof(char *));
	if (!split_path)
		exit(EXIT_FAILURE);
	i = 0;
	while (cp_split_path[i])
	{
		split_path[i] = ft_strjoin(cp_split_path[i], "/");
		free(cp_split_path[i]);
		i++;
	}
	split_path[i] = ft_find_dir(minishell, "PWD");
	split_path[i + 1] = NULL;
	free(cp_split_path);
	return (split_path);
}
