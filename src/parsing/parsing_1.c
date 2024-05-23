/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:49:32 by asangerm          #+#    #+#             */
/*   Updated: 2024/05/23 18:11:09 by asangerm         ###   ########.fr       */
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
	key = word_maker(line, i);
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

char	*semicolon_handler(char *line, t_data *data, int i, int j)
{
	char	*new_line;
	char	*tmp;

	tmp = NULL;
	new_line = NULL;
	while (line[i])
	{
		if (line[i] == '$')
		{
			tmp = gimme_str(line, j, i);
			new_line = ft_strcat(new_line, tmp);
			tmp = word_env_check(line, &i, data);
			if (tmp != NULL)
				new_line = ft_strcat(new_line, tmp);
			j = i;
		}
		if ((int)ft_strlen(line) > i)
			i++;
	}
	if (j == 0)
		return (line);
	tmp = gimme_str(line, j, i);
	new_line = ft_strcat(new_line, tmp);
	return (new_line);
}
