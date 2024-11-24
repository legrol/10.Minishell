/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:41:46 by pabromer          #+#    #+#             */
/*   Updated: 2024/11/08 10:32:51 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static char **ft_no_path(void)
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
	split_path[i+1] = NULL;
	free(cp_split_path);
	return (split_path);
}

