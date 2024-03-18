/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:48:41 by asangerm          #+#    #+#             */
/*   Updated: 2023/10/05 18:30:48 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*temp;

	temp = NULL;
	while (*s)
	{
		if (*s == (unsigned char)c)
			temp = s;
		s++;
	}
	if (*s == (unsigned char)c)
		temp = s;
	return ((char *)temp);
}

/*
#include <stdio.h>

int	main(int argc, char **argv)
{
	char	*temp;
	if (argc == 3)
	{
		temp = ft_strrchr(argv[1], argv[2][0]);
		printf("%ld\n", temp - argv[1]);
	}
	return (0);
}
*/