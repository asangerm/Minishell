/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:39:09 by asangerm          #+#    #+#             */
/*   Updated: 2023/10/24 14:10:58 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	res;

	res = 0;
	if (s == NULL)
	{
		res += ft_putstr_fd("(null)", 1);
		return (res);
	}
	while (*s)
	{
		res += ft_putchar_fd(*s, fd);
		s++;
	}
	return (res);
}
