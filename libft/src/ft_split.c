/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 22:04:02 by asangerm          #+#    #+#             */
/*   Updated: 2023/10/10 14:35:24 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (!(str[i] == c) && str[i])
		{
			count++;
			while (!(str[i] == c) && str[i])
				i++;
		}
	}
	return (count);
}

static char	*ft_gimme(char *str, int i, int j)
{
	char	*wrd;
	int		k;

	k = 0;
	wrd = malloc(sizeof(char) * (j - i + 1));
	while (i < j)
	{
		wrd[k] = str[i];
		k++;
		i++;
	}
	wrd[k] = '\0';
	return (wrd);
}

static char	*ft_checkwrd(int *j, char *str, char c)
{
	int		i;
	char	*wrd;

	i = *j;
	while (str[*j])
	{
		while (str[*j] == c && str[*j])
		{
			*j += 1;
			i++;
		}
		if (!(str[*j] == c) && str[*j])
		{
			while (!(str[*j] == c) && str[*j])
				*j += 1;
			wrd = ft_gimme(str, i, *j);
			return (wrd);
		}
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	char	*temp;
	int		len;
	int		i;
	int		j;

	temp = (char *)s;
	len = ft_count_words(temp, c);
	new = malloc(sizeof(char *) * (len + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		new[i] = ft_checkwrd(&j, temp, c);
		i++;
	}
	new[i] = (void *)0;
	return (new);
}
