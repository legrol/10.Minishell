/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:49:17 by pabromer          #+#    #+#             */
/*   Updated: 2024/09/24 12:22:15 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	size_t				r;
	const unsigned char	*src1;
	const unsigned char	*src2;

	src1 = (const unsigned char *) s1;
	src2 = (const unsigned char *) s2;
	if (n == 0)
		return (0);
	i = 0;
	while (i < n - 1 && src1[i] == src2[i])
		i++;
	r = src1[i] - src2[i];
	return (r);
}
