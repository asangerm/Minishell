/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:49:32 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/11 02:42:30 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*word_env_check(char *line, int *i, t_data *data)
{
	char	*key;
	char	*value;
	t_list	*list;

	value = NULL;
	(*i)++;
	key = word_maker_env(line, i);
	list = get_key(data, key);
	if (list != NULL)
		value = ft_strdup(((t_keyval *)list->content)->val);
	free(key);
	return (value);
}

char	*ft_strcat(char *str1, char *str2)
{
	char	*newstr;
	int		i;
	int		len1;

	if (str2 == NULL)
		return (str1);
	if (str1 == NULL)
		return (str2);
	len1 = ft_strlen(str1);
	newstr = malloc(sizeof(char) * (len1 + ft_strlen(str2) + 1));
	i = 0;
	while (str1[i])
	{
		newstr[i] = str1[i];
		i++;
	}
	while (str2[i - len1])
	{
		newstr[i] = str2[i - len1];
		i++;
	}
	newstr[i] = '\0';
	free(str1);
	free(str2);
	return (newstr);
}

char	*gimme_str(char *line, int j, int i)
{
	char	*newstr;
	int		k;

	if (i - j == 0)
		return (NULL);
	newstr = malloc(sizeof(char) * (i - j + 1));
	k = 0;
	while (k < (i - j))
	{
		newstr[k] = line[j + k];
		k++;
	}
	newstr[k] = '\0';
	return (newstr);
}

char	*process_dollar(char *line, t_data *data, t_indexes *ind, char *new)
{
	char	*tmp;

	tmp = NULL;
	tmp = gimme_str(line, ind->j, ind->i);
	new = ft_strcat(new, tmp);
	if (line[ind->i + 1] && line[ind->i + 1] == '?')
	{
		tmp = ft_itoa(last_signal);
		ind->i += 2;
	}
	else if (line[ind->i + 1] && line[ind->i + 1] == '$')
	{
		tmp = ft_itoa(data->ppid);
		ind->i += 2;
	}
	else if (!line[ind->i + 1] || (!ft_isalpha(line[ind->i + 1]) && line[ind->i + 1] != '_'))
	{
		ind->j = ind->i;
		ind->i++;
		return (new);
	}
	else
		tmp = word_env_check(line, &(ind->i), data);
	if (tmp != NULL)
		new = ft_strcat(new, tmp);
	ind->j = ind->i;
	return (new);
}

char	*semicolon_handler(char *line, t_data *data, int i, int j)
{
	char		*new_line;
	char		*tmp;
	t_indexes	indices;
	int			quote;

	new_line = NULL;
	tmp = NULL;
	indices.i = i;
	indices.j = j;
	quote = 0;
	while (line[indices.i])
	{
		if (line[indices.i] == '\"')
			quote++;
		if (quote % 2 == 0 && line[indices.i] == '\'')
			skip_quote(line, &(indices.i), '\'');
		if (line[indices.i] == '$')
			new_line = process_dollar(line, data, &indices, new_line);
		else
			indices.i++;
	}
	if (indices.j == 0)
		return (line);
	tmp = gimme_str(line, indices.j, indices.i);
	return (ft_strcat(new_line, tmp));
}
