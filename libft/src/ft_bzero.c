/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:25:38 by asangerm          #+#    #+#             */
/*   Updated: 2023/10/03 18:37:16 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

/*
#include <stdio.h>
#include <strings.h>

int	main(void)
{
	char	str1[50];
	char	str2[50];
	
	ft_bzero(str1, 5);
	bzero(str2,  5);
	printf("%s\n", str1);
	printf("%s\n", str2);
	return (0);
}
*/