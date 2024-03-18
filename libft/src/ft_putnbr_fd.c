/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:46:37 by asangerm          #+#    #+#             */
/*   Updated: 2023/10/24 14:10:22 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	int	res;

	res = 0;
	if (n == -2147483648)
		res += ft_putstr_fd("-2147483648", fd);
	else
	{
		if (n < 0)
		{
			res += ft_putchar_fd('-', fd);
			n = -n;
		}
		if (n >= 10)
		{
			res += ft_putnbr_fd(n / 10, fd);
			res += ft_putnbr_fd(n % 10, fd);
		}
		else
		{
			res += ft_putchar_fd(n + '0', fd);
		}
	}
	return (res);
}
