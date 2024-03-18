/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:36:57 by asangerm          #+#    #+#             */
/*   Updated: 2023/10/10 17:40:20 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(long int n)
{
	int	len;

	len = 0;
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int nbr)
{
	int			len;
	int			i;
	char		*new;
	long int	n;

	n = nbr;
	i = 0;
	len = ft_intlen(n);
	if (n <= 0)
		len++;
	new = ft_calloc(sizeof(char), (len + 1));
	if (!new)
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		i++;
		new[0] = '-';
	}
	while (len-- > i)
	{
		new[len] = (n % 10) + '0';
		n = n / 10;
	}
	return (new);
}
