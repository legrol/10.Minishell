/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:32:20 by pabromer          #+#    #+#             */
/*   Updated: 2024/09/24 12:55:22 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_convert(const char *c, va_list args, int i)
{
	size_t	a;

	a = 0;
	if (c[i + 1] == 'c')
		a = ft_putchar(va_arg(args, int));
	else if (c[i + 1] == 's')
		a = ft_putstr(va_arg(args, char *));
	else if (c[i + 1] == 'p')
		a = ft_putvoid(va_arg(args, uintptr_t));
	else if (c[i + 1] == 'd' || c[i + 1] == 'i')
		a = ft_putnbr(va_arg(args, int));
	else if (c[i + 1] == 'u')
		a = ft_putunbr(va_arg(args, unsigned int));
	else if (c[i + 1] == 'x' || c[i + 1] == 'X')
		a = ft_puthexa(va_arg(args, unsigned int), c[i + 1]);
	else if (c[i + 1] == '%')
		a = ft_putchar('%');
	return (a);
}

int	ft_printf(const char *str, ...)
{
	va_list	elements;
	size_t	count;
	size_t	i;

	va_start (elements, str);
	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			count = count + ft_convert(str, elements, i);
			i++;
		}
		else
			count += ft_putchar(str[i]);
		i++;
	}
	va_end (elements);
	return (count);
}

int	ft_putchar(char c)
{
	size_t	i;

	i = 0;
	write (1, &c, 1);
	i++;
	return (i);
}

int	ft_puthexa(unsigned long long n, char c)
{
	unsigned long long	i;

	i = 0;
	if (n >= 16)
		i += ft_puthexa(n / 16, c);
	if (c == 'x')
		ft_putchar("0123456789abcdef"[n % 16]);
	if (c == 'X')
		ft_putchar("0123456789ABCDEF"[n % 16]);
	i++;
	return (i);
}
int	ft_putnbr(int n)
{
	char	b;
	long	a;
	size_t	i;

	i = 0;
	a = (long) n;
	if (a < 0)
	{
		write (1, "-", 1);
		a = -a;
		i++;
	}
	if (a < 10)
	{
		b = a + 48;
		i += ft_putchar(b);
	}
	else
	{
		i += ft_putnbr(a / 10);
		i += ft_putnbr(a % 10);
	}
	return (i);
}
