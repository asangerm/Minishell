/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:07:16 by nfradet           #+#    #+#             */
/*   Updated: 2024/06/12 15:10:52 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	space_skipper(char *line, int *i)
{
	while (line[*i] && line[*i] == ' ')
		(*i)++;
}

int	is_only_space(char *line, int i)
{
	if (line[i] != ' ')
		return (0);
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<')
			return (1);
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	delim_set(t_prompt *prompt, char *word)
{
	if (prompt->delim)
		free(prompt->delim);
	prompt->delim = ft_strdup(word);
}

/*
	Ajoute une cmd au prompt
*/
void	cmd_handler(char *line, t_prompt *prompt, int *i)
{
	char	*word;

	word = next_arg(line, i);
	prompt->cmd = word;
}
