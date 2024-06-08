/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 04:02:12 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/08 21:42:16 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_quote(char *str, int *i, char quote)
{
	//ft_printf("%d\n", *i);
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
}

int	ft_newcount_words(char *str, char c)
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
			{
				if (str[i] == '\"')
					skip_quote(str, &i, '\"');
				else if (str[i] == '\'')
					skip_quote(str, &i, '\'');
				i++;
			}
		}
	}
	return (count);
}

char	*ft_newgimme(char *str, int i, int j)
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

char	*ft_newcheckwrd(int *j, char *str, char c)
{
	int		i;

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
			{
				if (str[*j] == '\"')
					skip_quote(str, j, '\"');
				else if (str[*j] == '\'')
					skip_quote(str, j, '\'');
				*j += 1;
			}
			return (ft_newgimme(str, i, *j));
		}
	}
	return (0);
}

char	**ft_newsplit(char const *s, char c)
{
	char	**new;
	char	*temp;
	int		len;
	int		i;
	int		j;

	temp = (char *)s;
	len = ft_newcount_words(temp, c);
	new = malloc(sizeof(char *) * (len + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		new[i] = ft_newcheckwrd(&j, temp, c);
		i++;
	}
	new[i] = (void *)0;
	return (new);
}