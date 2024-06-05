/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:20:09 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/03 17:01:45 by asangerm         ###   ########.fr       */
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
void	big_if(char *line, t_prompt *prompt, int *i)
{
	t_bool	space;

	space = false;
	while (line[*i])
	{
		if (line[*i] == '>')
			file_out_handler(line, prompt, i);
		else if (line[*i] == '<')
			file_in_handler(line, prompt, i);
		else if (!prompt->cmd && test_equal(line, i))
			var_handler(line, prompt, i);
		else if (!prompt->cmd)
			cmd_handler(line, prompt, i);
		else
			args_handler(line, prompt, i, space);
		if (line[*i] && line[*i] == ' ' && prompt->args)
			space = true;
		else
			space = false;
		while (line[*i] && line[*i] == ' ')
			(*i)++;
	}
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

/*
	parcours les prompt pour les découper
*/
void	lexer(t_prompt **prompt)
{
	t_prompt	*tmp;
	int			i;

	tmp = *prompt;
	while (tmp)
	{
		i = 0;
		while (tmp->line[i] == ' ')
			i++;
		big_if(tmp->line, tmp, &i);
		tmp = tmp->next;
	}
}

/*
	Cette fonction est la fonction qui execute toutes les autres,
	elle permet de parser, pour le moment elle peut extraire les
	fichiers de sortie et d'entrée de chaque prompt séparé par des
	pipes
*/
void	parse(char *line, t_prompt **prompt, t_data *data)
{
	char	*new_line;

	new_line = semicolon_handler(line, data, 0, 0);
	chain_creator(new_line, prompt);
	free(new_line);
	lexer(prompt);
}
