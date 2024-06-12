/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:20:09 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/12 15:39:30 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Determine quel type de donnée est le bout de line
*/
int	big_if(char *line, t_prompt *prompt, int *i)
{
	int	error;

	error = 0;
	while (line[*i])
	{
		if (line[*i] == '>')
			error = file_out_handler(line, prompt, i);
		else if (line[*i] == '<')
			error = file_in_handler(line, prompt, i);
		else if (!prompt->cmd && test_equal(line, i))
			var_handler(line, prompt, i);
		else if (!prompt->cmd)
			cmd_handler(line, prompt, i);
		else
			args_handler(line, prompt, i);
		while (line[*i] && line[*i] == ' ')
			(*i)++;
		if (error != 0)
			return (error);
	}
	return (error);
}

/*
	parcours les prompt pour les découper
*/
int	lexer(t_prompt **prompt)
{
	t_prompt	*tmp;
	int			i;
	int			error;

	tmp = *prompt;
	error = error_checker(tmp->line);
	if (error == 10)
		return (0);
	if (error != 0)
		return (error);
	while (tmp)
	{
		i = 0;
		while (tmp->line[i] == ' ')
			i++;
		error = big_if(tmp->line, tmp, &i);
		if (error != 0)
			return (error);
		tmp = tmp->next;
	}
	return (error);
}

int	quote_check(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
			if (!line[i])
				return (0);
		}
		else if (line[i] == '\"')
		{
			i++;
			while (line[i] && line[i] != '\"')
				i++;
			if (!line[i])
				return (0);
		}
		i++;
	}
	return (1);
}

int	pipe_check(char *line)
{
	int	i;
	int	valid;

	i = 0;
	valid = 0;
	while (line[i])
	{
		quote_skip(line, &i, &valid);
		if (line[i] != ' ' && line[i] != '|' && \
			line[i] != '<' && line[i] != '>')
			valid = 1;
		if (line[i] && line[i] == '|')
		{
			if (line[i + 1] && line[i + 1] == '|')
				if (valid == 0 || (line[i + 2] && line[i + 2] == '|'))
					return (ft_printf(SYNTH_ERROR, "||"), 0);
			if (valid == 0)
				return (ft_printf(SYNTH_ERROR, "|"), 0);
			valid = 0;
		}
		i++;
	}
	return (1);
}

/*
	Cette fonction est la fonction qui execute toutes les autres,
	elle permet de parser, pour le moment elle peut extraire les
	fichiers de sortie et d'entrée de chaque prompt séparé par des
	pipes
*/
int	parse(char *line, t_prompt **prompt, t_data *data)
{
	char	*new_line;

	if (line[0] == '\0')
		return (g_last_signal);
	if (!quote_check(line))
		return (ft_printf(QUOTE_ERROR), 2);
	new_line = semicolon_handler(line, data, 0, 0);
	if (!new_line)
		return (g_last_signal);
	if (!quote_check(new_line))
		return (ft_printf(QUOTE_ERROR), 2);
	if (!pipe_check(new_line))
		return (2);
	chain_creator(new_line, prompt);
	free(new_line);
	return (lexer(prompt));
}
