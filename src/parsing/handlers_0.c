/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:24:30 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/12 15:54:15 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*next_file(char *line, int *i)
{
	char	*word;

	word = next_arg(line, i);
	if (ft_strncmp(word, ">", 2) == 0)
	{
		free(word);
		return (ft_printf(SYNTH_ERROR, ">"), NULL);
	}
	else if (ft_strncmp(word, "<", 2) == 0)
	{
		free(word);
		return (ft_printf(SYNTH_ERROR, "<"), NULL);
	}
	else if (ft_strncmp(word, ">>", 2) == 0)
	{
		free(word);
		return (ft_printf(SYNTH_ERROR, ">>"), NULL);
	}
	else if (ft_strncmp(word, "<<", 2) == 0)
	{
		free(word);
		return (ft_printf(SYNTH_ERROR, "<<"), NULL);
	}
	return (word);
}

/*
	Ajoute un t_string file_out au prompt
*/
int	file_out_handler(char *line, t_prompt *prompt, int *i)
{
	char		*word;
	t_bool		type;

	(*i)++;
	type = false;
	if (!line[*i] || is_only_space(line, *i))
		return (ft_printf(SYNTH_ERROR, "newline"), 2);
	if ((line[*i] && line[*i] == '<') || !line[(*i) + 1] || \
		is_only_space(line, (*i) + 1))
		return (ft_printf(SYNTH_ERROR, "newline"), 2);
	if (line[*i] && line[*i] == '>')
	{
		if (!line[(*i) + 1] || is_only_space(line, (*i) + 1))
			return (ft_printf(SYNTH_ERROR, "newline"), 2);
		if (line[(*i) + 1] && line[(*i) + 1] == '>')
			return (ft_printf(SYNTH_ERROR, ">>"), 2);
		type = true;
		(*i)++;
	}
	space_skipper(line, i);
	word = next_file(line, i);
	if (word == NULL)
		return (2);
	return (str_add_back(&(prompt->file_out), new_str(word, type)), 0);
}

/*
	Ajoute un t_string file_in au prompt
*/
int	file_in_handler(char *line, t_prompt *prompt, int *i)
{
	char		*word;
	t_bool		type;

	(*i)++;
	type = false;
	if (!line[*i] || is_only_space(line, *i))
		return (ft_printf(SYNTH_ERROR, "newline"), 2);
	if ((line[*i] && line[*i] == '>') || !line[(*i) + 1] || \
		is_only_space(line, (*i) + 1))
		return (ft_printf(SYNTH_ERROR, "newline"), 2);
	if (line[*i] && line[*i] == '<')
	{
		if (the_weeknd(line, i) == 2)
			return (2);
		type = true;
	}
	space_skipper(line, i);
	word = next_file(line, i);
	if (word == NULL)
		return (2);
	if (type == true)
		delim_set(prompt, word);
	return (str_add_back(&(prompt->file_in), new_str(word, type)), 0);
}

/*
	Ajoute un t_string args au prompt
*/
void	args_handler(char *line, t_prompt *prompt, int *i)
{
	t_string	*new;
	char		*word;

	word = next_arg(line, i);
	if (ft_strlen(word) == 0)
		return ;
	new = new_str(word, 0);
	str_add_back(&(prompt->args), new);
}

void	var_handler(char *line, t_prompt *prompt, int *i)
{
	char		*word;
	t_list		*new;
	t_keyval	*kv;

	word = next_arg(line, i);
	kv = extract_var(word, false);
	free(word);
	new = ft_lstnew((void *)kv);
	ft_lstadd_back(&(prompt->var), new);
}
