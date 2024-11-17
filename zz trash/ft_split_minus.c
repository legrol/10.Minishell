/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:52:02 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/14 20:57:48 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "" xxx
 * 
 * @param		xxx
 * 
 * @return		xxx 
 * 
 */

static void	ft_free_str(int i, char **str)
{
	while (i > 0)
	{
		i--;
		free (*(str + i));
	}
	free(str);
}

static int	ft_count_word_len(char const *s, char c)
{
	int	i;

	i = 0;
	if (s[i] == '-')
		i++;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**ft_create_word(char const *s, char c, char **str, int words_count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < words_count)
	{
		while (s[j] && s[j] == 32)
			j++;
		str[i] = ft_substr(s, j, ft_count_word_len(&s[j], c));
		if (!str[i])
		{
			ft_free_str(i, str);
			return (NULL);
		}
		j += ft_count_word_len(&s[j], c);
		i++;
	}
	str[i] = NULL;
	return (str);
}

static int ft_count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && (s[i] != c))
				i++;
		}
		else
			i++;
	}
	return (count);	
}
char **ft_split_minus(char const *s, char c)
{
	char	**str;
	int		totalwords;

	if(!s)
		return (NULL);
	totalwords = ft_count_words(s, c);
	str = (char **) malloc((totalwords + 1) *(sizeof(char *)));
	if (!str)
		return (NULL);
	str = ft_create_word(s, c, str, totalwords);
	return (str);
}
