/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:37:38 by asangerm          #+#    #+#             */
/*   Updated: 2023/10/06 15:53:25 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	to_find_len;
	char	*temp;
	size_t	limit;

	to_find_len = (size_t)ft_strlen(to_find);
	temp = (char *)str;
	i = 0;
	if (to_find_len == 0)
		return (temp);
	while (str[i] && i < len)
	{
		if (to_find_len > len - i)
			return (NULL);
		else
			limit = to_find_len;
		if (str[i] == to_find[0] && ft_strncmp(str + i, to_find, limit) == 0)
			return (temp + i);
		i++;
	}
	return (NULL);
}
