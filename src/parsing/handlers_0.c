/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:24:30 by asangerm          #+#    #+#             */
/*   Updated: 2024/05/24 18:51:03 by asangerm         ###   ########.fr       */
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
	int			type;

	(*i)++;
	type = 1;
	if (line[*i] && line[*i] == '>')
	{
		type = 2;
		(*i)++;
	}
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	if (line[*i] == '\"')
		word = double_quote(line, i);
	else
		word = word_maker(line, i);
	new = new_str(word, type);
	str_add_back(&(prompt->file_out), new);
}

/*
	Ajoute un t_string file_in au prompt
*/
void	file_in_handler(char *line, t_prompt *prompt, int *i)
{
	char		*word;
	t_string	*new;
	int			type;

	(*i)++;
	type = 1;
	if (line[*i] && line[*i] == '<')
		{
			(*i)++;
			type = 2;
		}
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	if (line[*i] == '\"')
		word = double_quote(line, i);
	else
		word = word_maker(line, i);
	if (type == 1)
	{
		new = new_str(word, 0);
		return((void)str_add_back(&(prompt->file_in), new));
	}
	if (prompt->delim)
		free(prompt->delim);
	prompt->delim = word;
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
	if (ft_strlen(word) == 0)
		return;
	new = new_str(word, 0);
	str_add_back(&(prompt->args), new);
}

void	var_handler(char *line, t_prompt *prompt, int *i)
{
	char		*word;
	char		**splitted;
	t_list		*new;
	t_keyval	*kv;

	if (line[*i] == '\"')
		word = double_quote(line, i);
	else
		word = word_maker(line, i);
	splitted = split_var(word, 0, 0);
	free(word);
	kv = malloc(sizeof(t_keyval));
	kv->key = ft_strdup(splitted[0]);
	kv->val = ft_strdup(splitted[1]);
	kv->is_exported = false;
	new = ft_lstnew((void *)kv);
	ft_lstadd_back(&(prompt->var), new);
	free(splitted[0]);
	free(splitted[1]);
	free(splitted);
}
