/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:09:11 by asangerm          #+#    #+#             */
/*   Updated: 2023/10/24 14:17:25 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_convert_base(unsigned int nb, char *base)
{
	int				res;

	res = 0;
	if (nb >= 16)
	{
		res += ft_convert_base(nb / 16, base);
		res += ft_convert_base(nb % 16, base);
	}
	else
	{
		res += ft_putchar_fd(base[nb], 1);
	}
	return (res);
}

int	ft_convert_base_ptr(unsigned long nb, char *base)
{
	int	res;

	res = 0;
	if (nb >= 16)
	{
		res += ft_convert_base_ptr(nb / 16, base);
		res += ft_convert_base_ptr(nb % 16, base);
	}
	else
	{
		res += ft_putchar_fd(base[nb], 1);
	}
	return (res);
}

int	ft_putunsigned_fd(unsigned int n, int fd)
{
	int	res;

	res = 0;
	if (n >= 10)
	{
		res += ft_putnbr_fd(n / 10, fd);
		res += ft_putnbr_fd(n % 10, fd);
	}
	else
	{
		res += ft_putchar_fd(n + '0', fd);
	}
	return (res);
}

int	ft_hexconvert(unsigned long n, char c)
{
	char	*base;
	int		res;

	res = 0;
	if (c == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (c == 'p')
	{
		if (n == 0)
		{
			res += ft_putstr_fd("(nil)", 1);
			return (res);
		}
		res += ft_putstr_fd("0x", 1);
		res += ft_convert_base_ptr(n, base);
		return (res);
	}
	res += ft_convert_base(n, base);
	return (res);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		res;

	va_start(args, format);
	res = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			res += ft_format(*format, args);
		}
		else
			res += ft_putchar_fd(*format, 1);
		format++;
	}
	va_end(args);
	return (res);
}
