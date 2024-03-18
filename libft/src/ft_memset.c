/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:00:53 by asangerm          #+#    #+#             */
/*   Updated: 2023/10/03 18:18:34 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	void	*temp;

	temp = s;
	i = 0;
	while (i < n)
	{
		*(unsigned char *)s = c;
		i++;
		s++;
	}
	return (temp);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	str[50];
	printf("%s\n", ft_memset(str, 'a', 5));
	printf("%s\n", memset(str, 'a', 5));
}
*/