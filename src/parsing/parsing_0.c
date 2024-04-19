/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:20:09 by asangerm          #+#    #+#             */
/*   Updated: 2024/04/20 01:12:26 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Cette fonction alloue et renvoie le nom du fichier de
	redirection de manière clean, oue je me sauce ya quoi?
*/
char	*word_maker(char *line, int i, int j, int l)
{
	char	*word;
	int		k;

	word = malloc(sizeof(char) * (j - i - 1));
	if (line[j - 1] == '\"')
		j -= 2;
	else if (line[j - 1] == ' ')
		j--;
	k = i + l;
	while (i++ != j)
		word[i - k + (l - 1)] = line[i + (l - 1)];
	word[i - k - (l - 1)] = '\0';
	return (word);
}

/*
	Cette fonction recherche dans le prompt si il y a des des
	redirections et renvoie le fichier ciblé par la redirection
*/
char	*file_finder(int i, char *line)
{
	int		j;
	int		l;

	j = i + 1;
	l = 0;
	while (line[j] == ' ')
		j++;
	i = j;
	if (line[j++] == '\"')
	{
		while (line[j++] != '\"')
		{
		}
		l = 1;
	}
	else
	{
		while (line[j] != '\0' && line[j] != ' ')
			j++;
	}
	return (word_maker(line, i, j, l));
}

/*
	Cette fonction permet de venir stocker dans la structure
	prompt les fichiers d'entrée et de sortie si ils existent
*/
void	redirection_handler(t_prompt **prompt)
{
	t_prompt	*tmp;
	int			i;

	tmp = *prompt;
	while (tmp)
	{
		i = 0;
		while (tmp->line[i])
		{
			if (tmp->line[i] == '>' )
			{
				if (tmp->file_out)
					free(tmp->file_out);
				tmp->file_out = file_finder(i, tmp->line);
			}
			if (tmp->line[i] == '<' )
			{
				if (tmp->file_in)
					free(tmp->file_in);
				tmp->file_in = file_finder(i, tmp->line);
			}
			i++;
		}
		tmp = tmp->next;
	}
}
/*
	Fonction qui s'occupe de récup et stocker la commande
	et les arguments du prompt
*/
void	cmd_handler(t_prompt **prompt)
{
	t_prompt	*tmp;

	tmp = *prompt;
	while (tmp)
	{
		tmp->cmd = cmd_finder(tmp->line);
		tmp->args = args_finder(tmp->line);
		tmp = tmp->next;
	}
}

/*
	Cette fonction est la fonction qui execute toutes les autres,
	elle permet de parser, pour le moment elle peut extraire les
	fichiers de sortie et d'entrée de chaque prompt séparé par des
	pipes
*/
void	parse(char *line, t_prompt **prompt)
{
	chain_creator(line, prompt);
	redirection_handler(prompt);
	cmd_handler(prompt);
}
