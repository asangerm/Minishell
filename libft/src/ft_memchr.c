/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:42:14 by asangerm          #+#    #+#             */
/*   Updated: 2023/10/03 19:17:59 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	ch;

	str = (unsigned char *)s;
	ch = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (*str == ch)
			return (str);
		str++;
		i++;
	}
	return (NULL);
}

/*
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int	main(void)
{
	int tab[7] = {-49, 49, 1, -1, 0, -2, 2};
	printf("%s\n%s", (char *)ft_memchr(tab, -1, 7), (char *)memchr(tab, -1, 7));
	return (0);
}
*/