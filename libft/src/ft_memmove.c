/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:11:32 by pabromer          #+#    #+#             */
/*   Updated: 2024/09/24 12:22:23 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned char	*destbsrc(unsigned char *d, unsigned char *s,
size_t len)
{
	int	i;

	i = len - 1;
	while (i >= 0)
	{
		d[i] = s[i];
		i--;
	}
	return (d);
}

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	int				i;
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *) dest;
	s = (unsigned char *) src;
	if (s == d || len == 0)
		return (dest);
	if (d > s && d - s < (int)len)
	{
		destbsrc(d, s, len);
		return (dest);
	}
	if (s > d && s - d < (int)len)
	{
		i = 0;
		while (i < (int)len)
		{
			d[i] = s[i];
			i++;
		}
		return (dest);
	}
	ft_memcpy(dest, src, len);
	return (dest);
}
