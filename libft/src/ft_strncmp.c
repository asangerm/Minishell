/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:37:51 by asangerm          #+#    #+#             */
/*   Updated: 2023/10/06 16:32:28 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < (n - 1) && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((int)((unsigned char)s1[i] - (unsigned char)s2[i]));
		i++;
	}
	return ((int)((unsigned char)s1[i] - (unsigned char)s2[i]));
}

/*
#include <string.h>
#include <stdio.h>

int	main()
{
	char *s1 = "\x12\xff\x65\x12\xbd\xde\xad";
 	char *s2 = "\x12\x02";
 	size_t size = 6;
	printf("%d\n", ft_strncmp(s1, s2, size));
	printf("%d\n", strncmp(s1, s2, size));
	return (0);
}
*/
