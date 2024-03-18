/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:45:09 by asangerm          #+#    #+#             */
/*   Updated: 2023/10/04 18:59:03 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	src_len;
	size_t	cpy_len;

	src_len = ft_strlen(src);
	if (src_len < size - 1)
		cpy_len = src_len;
	else
		cpy_len = size - 1;
	if (size != 0)
	{
		ft_memcpy(dest, src, cpy_len);
		dest[cpy_len] = '\0';
	}
	return (src_len);
}
