/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extracters_0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:58:06 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/05 16:32:34 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int			j;

	j = *i;
	while (line[j] && line[j] != ' ' && line[j] != '\"' && line[j] != '\'')
		j++;
	word = malloc(sizeof(char) * (j - *i + 1));
	j = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\"' && line[*i] != '\'')
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
	int			j;

	j = *i;
	while (line[j] && line[j] != ' ' && line[j] != '\"' && line[j] != '\'' && line[j] != '=' && line[j] != '$')
		j++;
	word = malloc(sizeof(char) * (j - *i + 1));
	j = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\"' && line[*i] != '\'' && line[*i] != '=' && line[*i] != '$')
	{
		word[*i - j] = line[*i];
		(*i)++;
	}
	word[*i - j] = '\0';
	return (word);
}