/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:20:09 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/06 04:38:02 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*next_arg(char *line, int *i)
{
	char		*word;
	char		*str;

	str = NULL;
	while (line[*i] && line[*i] != ' ')
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

/*
	Determine quel type de donnée est le bout de line
*/
int	big_if(char *line, t_prompt *prompt, int *i)
{
	int	error;

	error = 1;
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
		if (error == 0)
			return (0);
	}
	return (1);
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

int	error_checker(char *line)
{
	int	i;

	i = 0;
	if (line[i] && line[i] == ':' && !line[i + 1])
		return (0);
	else if (line[i] && line[i] == '!' && !line[i + 1])
		return (0);
	return (1);
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
	error = 1;
	if (!tmp || error_checker(tmp->line) == 0)
		return (0);
	while (tmp)
	{
		i = 0;
		while (tmp->line[i] == ' ')
			i++;
		error = big_if(tmp->line, tmp, &i);
		if (error == 0)
			return (0);
		tmp = tmp->next;
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
	int		error;

	error = 1;
	new_line = semicolon_handler(line, data, 0, 0);
	if (!new_line)
		return (error);
	chain_creator(new_line, prompt);
	free(new_line);
	error = lexer(prompt);
	return (error);
}
