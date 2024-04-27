/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_chain_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:54:28 by asangerm          #+#    #+#             */
/*   Updated: 2024/04/25 15:55:03 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Permet d'afficher le contenu des listes t_string du prompt
*/
void	tab_display(t_string **tab, char *type)
{
	t_string	*tmp;
	int			j;

	if (*tab)
	{
		j = 0;
		tmp = *tab;
		while (tmp)
		{
			ft_printf("	%s number %d = #%s#\n", type, j, tmp->str);
			j++;
			tmp = tmp->next;
		}
	}
	else
		ft_printf("	%s = >%s<\n", type, NULL);
}

/*
	Au bout d'un moment tu sais lire l'anglais non?
	chain_display c'est assez explicite c******
*/
void	chain_display(t_prompt **prompt)
{
	t_prompt	*tmp;
	int			i;

	tmp = *prompt;
	i = 0;
	while (tmp)
	{
		ft_printf("Prompt number %d:\n", i);
		ft_printf("	line = #%s#\n", tmp->line);
		ft_printf("	cmd = #%s#\n", tmp->cmd);
		tab_display(&(tmp->file_in), "file_in");
		tab_display(&(tmp->file_out), "file_out");
		tab_display(&(tmp->args), "args");
		tmp = tmp->next;
		i++;
	}
}

/*
	Cette fonction créé la liste chainée de prompt séparés
	par des pipes
*/
void	chain_creator(char *line, t_prompt **prompt)
{
	int			i;
	char		**split_line;
	t_prompt	*tmp;

	split_line = ft_split(line, '|');
	i = 0;
	while (split_line[i])
	{
		tmp = new_prompt(split_line[i]);
		prompt_add_back(prompt, tmp);
		i++;
	}
}
