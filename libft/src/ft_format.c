/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:12:49 by asangerm          #+#    #+#             */
/*   Updated: 2023/10/24 14:13:26 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_format(const char format, va_list args)
{
	int	res;

	res = 0;
	if (format == 'c')
		res += ft_putchar_fd(va_arg(args, int), 1);
	if (format == 'u')
		res += ft_putunsigned_fd(va_arg(args, unsigned int), 1);
	if (format == 'i' || format == 'd')
		res += ft_putnbr_fd(va_arg(args, int), 1);
	if (format == 's')
		res += ft_putstr_fd(va_arg(args, char *), 1);
	if (format == '%')
		res += ft_putchar_fd('%', 1);
	if (format == 'x' || format == 'X' || format == 'p')
		res += ft_hexconvert(va_arg(args, unsigned long int), format);
	return (res);
}
