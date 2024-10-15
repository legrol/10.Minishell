/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:07:17 by pabromer          #+#    #+#             */
/*   Updated: 2024/09/24 12:21:53 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	int	b;

	b = 0;
	if ((c > 64 && c < 91) || (c > 96 && c < 123))
		b = 1;
	return (b);
}
