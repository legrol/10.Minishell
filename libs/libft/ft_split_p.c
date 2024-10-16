/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:27:39 by pabromer          #+#    #+#             */
/*   Updated: 2024/10/16 15:42:30 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static unsigned int	mallocsize_m(char const *s, char c)
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

static void	*freessplit_m(char **ssplit, int k)
{
	while (k >= 0)
	{
		free(ssplit[k]);
		k--;
	}
	free(ssplit);
	return (NULL);
}

static char	**fillsplit_m(char **ssplit, char const *s, char c)
{
	size_t	i;
	int		j;
	size_t	k;

	i = 0;
	k = 0;
	j = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && j == -1)
			j = i;
		else if ((s[i] == c || i == ft_strlen(s)) && j != -1)
		{
			ssplit[k] = ft_substr(s, j, i - j);
			if (!ssplit[k])
				if (freessplit_m(ssplit, k) == NULL)
					return (NULL);
			k++;
			j = -1;
		}
		i++;
	}
	ssplit[k] = NULL;
	return (ssplit);
}

char	**ft_split_m(char const *s, char c)
{
	char	**ssplit;

	ssplit = (char **)malloc((mallocsize_m(s, c) + 1) * sizeof(char *));
	if (!ssplit)
		return (NULL);
	ssplit = fillsplit_m(ssplit, s, c);
	if (!ssplit)
		return (freessplit_m(ssplit, mallocsize_m(s, c)));
	return (ssplit);
}
