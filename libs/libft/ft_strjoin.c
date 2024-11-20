/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:18:28 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/08/24 14:18:28 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include "../../includes/minishell.h"
#define MAX_STR_LEN 4096



// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*str3;
// 	int		totallen;
// 	int		i;
// 	int		j;

// 	totallen = ft_strlen(s1) + ft_strlen(s2);
// 	i = 0;
// 	j = 0;
// 	str3 = (char *) malloc((totallen + 1) * sizeof(char));
// 	if (!str3)
// 		return (0);
// 	while (s1[i] != '\0')
// 	{
// 		str3[i] = s1[i];
// 		i++;
// 	}
// 	while (s2[j] != '\0')
// 	{
// 		str3[i] = s2[j];
// 		i++;
// 		j++;
// 	}
// 	str3[i] = '\0';
// 	return (str3);
// }

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str3;
	int		totallen;
	int		i;
	int		j;

	if (!s1 || !s2)
	{
		ft_printf("ft_strjoin: One of the inputs is NULL\n");
		return (NULL);
	}
	totallen = ft_strlen(s1) + ft_strlen(s2);
	if (totallen <= 0 || totallen > MAX_STR_LEN)
	{
		fprintf(stderr, "ft_strjoin: Invalid string length %d\n", totallen);
		return (NULL);
	}
	str3 = (char *) malloc((totallen + 1) * sizeof(char));
	if (!str3)
	{
		ft_printf("ft_strjoin: Malloc failed for size %d\n", \
		totallen + 1);
		return (NULL);
	}
	i = 0;
	while (s1[i] != '\0')
	{
		str3[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		str3[i] = s2[j];
		i++;
		j++;
	}
	str3[i] = '\0';
	ft_printf("ft_strjoin: Resulting string: %s\n", str3);
	return (str3);
}
