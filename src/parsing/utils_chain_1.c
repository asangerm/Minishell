/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_chain_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:54:28 by asangerm          #+#    #+#             */
/*   Updated: 2024/04/19 17:26:27 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Au bout d'un moment tu sais lire l'anglais non?
	chain_display c'est assez explicite c******
*/
void	chain_display(t_prompt **prompt)
{
	t_prompt	*tmp;
	int			i;
	int			j;

	tmp = *prompt;
	i = 0;
	while (tmp)
	{
		ft_printf("Prompt number %d:\n", i);
		ft_printf("	line = #%s#\n", tmp->line);
		ft_printf("	cmd = #%s#\n", tmp->cmd);
		ft_printf("	file_in = #%s#\n", tmp->file_in);
		ft_printf("	file_out = #%s#\n", tmp->file_out);
		j = 0;
		if (tmp->args)
		{
			while (tmp->args[j])
			{
				ft_printf("	arg number %d = >%s<\n", j, tmp->args[j]);
				j++;
			}
		}
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
