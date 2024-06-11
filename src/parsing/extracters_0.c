/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extracters_0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:58:06 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/11 02:19:51 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

char	*simple_quote(char *line, int *i)
{
	int		j;
	char	*word;

	(*i)++;
	j = *i;
	while (line[j] && line[j] != '\'')
		j++;
	word = malloc(sizeof(char) * (j - *i + 1));
	j = *i;
	while (line[*i] && line[*i] != '\'')
	{
		word[*i - j] = line[*i];
		(*i)++;
	}
	word[*i - j] = '\0';
	(*i)++;
	return (word);
}

/*
	extrait un char * d'un bout de line entre double quotes
*/
char	*double_quote(char *line, int *i)
{
	int		j;
	char	*word;

	(*i)++;
	j = *i;
	while (line[j] && line[j] != '\"')
		j++;
	word = malloc(sizeof(char) * (j - *i + 1));
	j = *i;
	while (line[*i] && line[*i] != '\"')
	{
		word[*i - j] = line[*i];
		(*i)++;
	}
	word[*i - j] = '\0';
	(*i)++;
	return (word);
}

/*
	extrait un char * d'un bout de line entre deux espaces
*/
char	*word_maker(char *line, int *i)
{
	char		*word;
	char		*str;
	int			j;

	str = " \'\"<>";
	j = *i;
	while (line[j] && !is_in(str, line[j]))
		j++;
	word = malloc(sizeof(char) * (j - *i + 1));
	j = *i;
	while (line[*i] && !is_in(str, line[*i]))
	{
		word[*i - j] = line[*i];
		(*i)++;
	}
	word[*i - j] = '\0';
	return (word);
}

char	*word_maker_env(char *line, int *i)
{
	char		*word;
	char		*str;
	int			j;

	str = "$[]{}\'\" =?%!@*/<>.#-+:()&^";
	j = *i;
	while (line[j] && !is_in(str, line[j]))
		j++;
	word = malloc(sizeof(char) * (j - *i + 1));
	j = *i;
	while (line[*i] && !is_in(str, line[*i]))
	{
		word[*i - j] = line[*i];
		(*i)++;
	}
	word[*i - j] = '\0';
	return (word);
}
