/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:18:12 by asangerm          #+#    #+#             */
/*   Updated: 2023/10/04 18:06:05 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	d = (char *)dest;
	s = (char *)src;
	i = 0;
	if (dest == (void *)0 && src == (void *)0)
		return (NULL);
	if (d > s)
		while (n-- > 0)
			d[n] = s[n];
	else
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}

/*
#include <string.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	void	*dest;
	void	*dest2;

	dest = argv[1];
	dest2 = argv[1];
	if (argc == 4)
	{
		dest = memmove(dest, argv[2], atoi(argv[3]));
		dest2 = memcpy(dest2, argv[2], atoi(argv[3]));
	}
	printf("memmove :\ndest : %s, src : %s, n : %d\n", (char *)dest,
	 argv[2], atoi(argv[3]));
	printf("memcpy :\ndest : %s, src : %s, n : %d\n", (char *)dest2,
	 argv[2], atoi(argv[3]));
	return (0);
}
*/