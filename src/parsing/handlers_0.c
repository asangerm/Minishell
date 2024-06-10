/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:24:30 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/10 18:35:54 by nfradet          ###   ########.fr       */
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

char	*next_file(char *line, int *i)
{
	char *word;

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
	t_string	*new;
	t_bool		type;

	(*i)++;
	type = false;
	if (!line[*i] || is_only_space(line, *i))
		return(ft_printf(SYNTH_ERROR, "newline"), 2);
	if (line[*i] && line[*i] == '>')
	{
		if (!line[(*i) + 1] || is_only_space(line, (*i) + 1))
			return(ft_printf(SYNTH_ERROR, "newline"), 2);
		if (line[(*i) + 1] && line[(*i) + 1] == '>')
			return(ft_printf(SYNTH_ERROR, ">>"), 2);
		type = true;
		(*i)++;
	}
	space_skipper(line, i);
	word = next_file(line, i);
	if (word == NULL)
		return (2);
	new = new_str(word, type);
	return (str_add_back(&(prompt->file_out), new), 0);
}

void	delim_set(t_prompt *prompt, char *word)
{
	if (prompt->delim)
		free(prompt->delim);
	prompt->delim = ft_strdup(word);
}

/*
	Ajoute un t_string file_in au prompt
*/
int	file_in_handler(char *line, t_prompt *prompt, int *i)
{
	char		*word;
	t_string	*new;
	t_bool		type;

	(*i)++;
	type = false;
	if (!line[*i] || is_only_space(line, *i))
		return(ft_printf(SYNTH_ERROR, "newline"), 2);
	if ((line[*i] && line[*i] == '>') && (!line[(*i) + 1] || is_only_space(line, (*i) + 1)))
		return(ft_printf(SYNTH_ERROR, "newline"), 2);
	if (line[*i] && line[*i] == '<')
	{
		if (!line[(*i) + 1] || is_only_space(line, (*i) + 1))
			return(ft_printf(SYNTH_ERROR, "newline"), 2);
		if (line[(*i) + 1] && line[(*i) + 1] == '<')
			return(ft_printf(SYNTH_ERROR, "<<"), 2);
		(*i)++;
		type = true;
	}
	space_skipper(line, i);
	word = next_file(line, i);
	if (word == NULL)
		return (2);
	if (type == true)
		delim_set(prompt, word);
	new = new_str(word, type);
	return (str_add_back(&(prompt->file_in), new), 0);
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
	char		**splitted;
	t_list		*new;
	t_keyval	*kv;

	word = next_arg(line, i);
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
