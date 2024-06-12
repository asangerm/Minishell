/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:07:16 by nfradet           #+#    #+#             */
/*   Updated: 2024/06/12 15:47:01 by asangerm         ###   ########.fr       */
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

int	the_weeknd(char *line, int *i)
{
	if (!line[(*i) + 1] || is_only_space(line, (*i) + 1))
		return (ft_printf(SYNTH_ERROR, "newline"), 2);
	if (line[(*i) + 1] && line[(*i) + 1] == '<')
		return (ft_printf(SYNTH_ERROR, "<<"), 2);
	(*i)++;
	return (0);
}
