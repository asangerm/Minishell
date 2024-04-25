/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:24:30 by asangerm          #+#    #+#             */
/*   Updated: 2024/04/25 16:50:04 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Ajoute un t_string file_out au prompt
*/
void	file_out_handler(char *line, t_prompt *prompt, int *i)
{
	char		*word;
	t_string	*new;

	(*i)++;
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	if (line[*i] == '\"')
		word = double_quote(line, i);
	else
		word = word_maker(line, i);
	new = new_str(word);
	str_add_back(&(prompt->file_out), new);
}

/*
	Ajoute un t_string file_in au prompt
*/
void	file_in_handler(char *line, t_prompt *prompt, int *i)
{
	char		*word;
	t_string	*new;

	(*i)++;
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	if (line[*i] == '\"')
		word = double_quote(line, i);
	else
		word = word_maker(line, i);
	new = new_str(word);
	str_add_back(&(prompt->file_in), new);
}

/*
	Ajoute une cmd au prompt
*/
void	cmd_handler(char *line, t_prompt *prompt, int *i)
{
	if (line[*i] == '\"')
		prompt->cmd = double_quote(line, i);
	else
		prompt->cmd = word_maker(line, i);
}

/*
	Ajoute un t_string args au prompt
*/
void	args_handler(char *line, t_prompt *prompt, int *i)
{
	t_string	*new;
	char		*word;

	if (line[*i] == '\"')
		word = double_quote(line, i);
	else
		word = word_maker(line, i);
	new = new_str(word);
	str_add_back(&(prompt->args), new);
}
