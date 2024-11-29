/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:00:30 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/28 17:00:02 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_find_special_char" searches for the first non-alphanumeric
 * character in a given string `s` that is not an underscore (`_`).
 * 
 * - If no special character is found, it returns `'\0'`.
 * - Used to identify delimiters for variable expansion in the shell.
 * 
 * @param char *s	The input string to search for special characters.
 * 
 * @return char		The first special character found or `'\0'` if none exists.
 * 
 * The function "ft_split_expand_join" joins an array of substrings into a 
 * single string. It dynamically allocates memory for the result and ensures 
 * memory is freed for intermediate steps.
 * 
 * - Iterates through the array of substrings (`split`), joining them one by 
 *   one.
 * - Frees the previously allocated memory for intermediate results.
 * 
 * - Example:
 *   Input: `split = {"echo", " ", "$USER"}`
 *   Output: `"echo $USER"`
 * 
 * @param char **split	An array of strings to be joined.
 * 
 * @return char*		A dynamically allocated string containing the 
 * 						concatenated substrings, or `NULL` if memory 
 * 						allocation fails.
 * 
 * The function "ft_only_expand_join" retrieves the appropriate value for 
 * expansion based on the shell's state or environment variables.
 * 
 * - If `f == 1`, it expands `$?` using the shell's last exit status.
 * - Otherwise, it searches for the variable in the environment.
 * 
 * @param t_minishell *minishell	The shell's state structure.
 * @param char *join				The variable name to expand.
 * @param int f						Flag indicating special expansion for `$?`.
 * 
 * @return char*					A dynamically allocated string containing 
 *									the expanded value or `NULL` if not found.
 * 
 * The function "ft_change_token" creates a new token by joining a temporary 
 * string and a special substring, ensuring proper memory management.
 * 
 * - If `temp` is `NULL`, it duplicates `sp` directly.
 * - Frees memory for `temp`, `join`, and `sp` to avoid memory leaks.
 * 
 * @param char *temp	A temporary string used in the join process.
 * @param char *sp		A substring or special string to append.
 * 
 * @return char*		A new dynamically allocated string containing the 
 * 						result.
 * 
 * The function "ft_count_dollar" counts the occurrences of the `$` character 
 * in a string and calculates the total size needed to prepare the string for 
 * splitting. It adds additional space for inserting newlines after each `$`.
 * 
 * - Iterates through the string, counting occurrences of `$`.
 * - Returns the total length of the string plus the count of `$` characters, 
 *   plus one for the null terminator.
 * 
 * @param char *s	The input string to analyze.
 * 
 * @return int		The total size required to prepare the string for splitting.
 * 
 */

/*int	ft_count_dollar(char *s)
{
	int	c;
	int	i;

	i = 0;
	c = 0;
	while (s[i])
	{
		if (s[i] == '$')
			c++;
		i++;
	}
	return (i + c + 1);
}

char	*ft_change_token(char *temp, char *sp)
{
	char	*t;
	char	*join;

	if (!temp)
		join = ft_strdup(sp);
	else
		join = ft_strjoin(temp, sp);
	t = ft_strdup(join);
	if (temp)
		free(temp);
	free(join);
	free(sp);
	return (t);
}

char	*ft_only_expand_join(t_minishell *minishell, char *join, int f)
{
	char	*temp;

	if (f == 1)
		temp = ft_itoa(minishell->exit);
	else
	{
		if (ft_find_dir(minishell, join))
			temp = ft_strdup(ft_find_dir(minishell, join));
		else
			temp = NULL;
	}
	return (temp);
}

char	*ft_split_expand_join(char **split)
{
	char	*temp;
	char	*temp2;
	int		i;

	temp = split[0];
	i = 1;
	while (split[i])
	{
		temp2 = ft_strjoin(temp, split[i]);
		free(temp);
		temp = temp2;
		i++;
	}
	i = 0;
	return (temp);
}

char	ft_find_special_char(char *s)
{
	int	i;

	if (!s)
		return ('\0');
	i = 0;
	while (s[i])
	{
		if (ft_isalnum(s[i]) == 0 && s[i] != '_')
			return (s[i]);
		i++;
	}
	return ('\0');
}*/
