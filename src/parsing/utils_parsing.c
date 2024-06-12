/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:57:27 by nfradet           #+#    #+#             */
/*   Updated: 2024/06/12 15:01:20 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_checker(char *line)
{
	int	i;

	i = 0;
	if (line[i] && line[i] == ':' && !line[i + 1])
		return (10);
	else if (line[i] && line[i] == '#' && !line[i + 1])
		return (10);
	else if (line[i] && line[i] == '!' && !line[i + 1])
		return (1);
	return (0);
}

void	string_tab_display(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		ft_printf("arg %d = #%s#\n", i, args[i]);
		i++;
	}
}

char	*next_arg(char *line, int *i)
{
	char		*word;
	char		*str;

	str = NULL;
	while (line[*i] && line[*i] != ' ' && line[*i] != '<' && line[*i] != '>')
	{
		if (line[*i] == '\"')
			word = double_quote(line, i);
		else if (line[*i] == '\'')
			word = simple_quote(line, i);
		else
			word = word_maker(line, i);
		str = ft_strcat(str, word);
	}
	return (str);
}

void	quote_skip(char *line, int	*i, int *valid)
{
	if (line[*i] == '\'')
	{
		(*i)++;
		while (line[*i] && line[*i] != '\'')
			(*i)++;
		if (line[*i])
			*valid = 1;
	}
	else if (line[*i] == '\"')
	{
		(*i)++;
		while (line[*i] && line[*i] != '\"')
			(*i)++;
		if (line[*i])
			*valid = 1;
	}
}
