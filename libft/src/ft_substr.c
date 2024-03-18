/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:57:44 by asangerm          #+#    #+#             */
/*   Updated: 2023/10/09 21:23:30 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*newstr;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		newstr = malloc(sizeof(char) * 1);
		*newstr = '\0';
		return (newstr);
	}
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	newstr = malloc((len + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	ft_strlcpy(newstr, s + start, len + 1);
	newstr[len] = '\0';
	return (newstr);
}
