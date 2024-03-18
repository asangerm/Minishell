/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:46:22 by asangerm          #+#    #+#             */
/*   Updated: 2023/10/27 15:32:15 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*new;
	size_t	j;
	size_t	i;

	i = 0;
	j = 0;
	new = malloc((ft_strlen(s2) + ft_strlen(s1) + 1) * sizeof(char));
	if (!new)
		return (NULL);
	while (s1[i])
	{
		new[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i])
	{
		new[j++] = s2[i++];
	}
	new[ft_strlen(s2) + ft_strlen(s1)] = '\0';
	if (s1)
		free(s1);
	return (new);
}

int	ft_strlen_endl(char	*str)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != '\n')
	{
		len++;
	}
	return (len);
}
