/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:11:55 by asangerm          #+#    #+#             */
/*   Updated: 2023/10/05 17:17:55 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ss1;
	const unsigned char	*ss2;
	size_t				i;

	i = 0;
	ss1 = (const unsigned char *)s1;
	ss2 = (const unsigned char *)s2;
	while (i < n)
	{
		if (ss1[i] != ss2[i])
			return (ss1[i] - ss2[i]);
		i++;
	}
	return (0);
}

/*
#include <string.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	if (argc == 4)
	{
		printf("%d\n", ft_memcmp(argv[1], argv[2], atoi(argv[3])));
		printf("%d\n", memcmp(argv[1], argv[2], atoi(argv[3])));
	}
	return (0);
}
*/