/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:47:11 by pabromer          #+#    #+#             */
/*   Updated: 2024/09/24 12:22:07 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digit(int n)
{
	int		i;

	if (n == 0)
		return (1);
	i = 0;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*num;
	long	tmp;

	tmp = n;
	i = digit(tmp);
	if (n < 0)
	{
		tmp = -tmp;
		i++;
	}
	num = (char *)malloc(i + 1);
	if (!num)
		return (NULL);
	num[i] = '\0';
	while (i-- > 0)
	{
		num[i] = (tmp % 10) + '0';
		tmp = tmp / 10;
	}
	if (n < 0)
		num[0] = '-';
	return (num);
}
