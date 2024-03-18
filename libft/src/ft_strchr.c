/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:33:23 by asangerm          #+#    #+#             */
/*   Updated: 2023/10/06 19:37:42 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*temp;
	char	*temp2;
	temp2 = strchr("tripouille", 't' + 256);
	temp = ft_strchr("tripouille", 't' + 256);
	printf("MINE: %s\nREAL: %s\n", temp, temp2);
	printf("%c\n", 't' + 256);
	return (0);
}
*/
