/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 00:14:14 by asangerm          #+#    #+#             */
/*   Updated: 2024/04/20 01:29:17 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Fonction qui compte combien de caractère il faut pour la commande
*/
int	cmd_counter(char *line, int i)
{
	int	l;

	l = 0;
	while (line[i] != ' ')
	{
		i++;
		l++;
	}
	return (l);
}

/*
	Fonction qui permet de skip ce qui concerne les redirections
	pour aller directement à l'endroit dans le prompt qui contient
	la commande
*/
int	skip_redirection(char *line, int i)
{
	i++;
	while (line[i] == ' ' && line[i])
		i++;
	if (line[i] == '\"' && line[i])
	{
		i++;
		while (line[i] != '\"' && line[i])
			i++;
		i++;
	}
	else
	{
		while (line[i] != ' ' && line[i])
			i++;
	}
	while (line[i] == ' ' && line[i])
		i++;
	return(i);
}

/*
	Fonction qui vient extraire la commande du prompt
*/
char		*cmd_finder(char *line)
{
	char	*cmd;
	int		i;
	int		len;
	int		j;

	i = 0;
	while (line[i] == ' ')
		i++;
	while (line[i] == '>' || line[i] == '<')
		i = skip_redirection(line, i);
	len = cmd_counter(line, i);
	cmd = malloc(sizeof(char) * (len + 1));
	j = i;
	while (line[i] != ' ')
	{
		cmd[i - j] = line[i];
		i++;
	}
	cmd[i - j] = '\0';
	return(cmd);
}

char	*args_copy(char *line, int i)
{
	char	*cpy;
	int		j;
	int		k;

	j = 0;
	k = i;
	while (line[k] && line[k] != '>' && line[k] != '<')
	{
		j++;
		k++;
	}
	cpy = malloc(sizeof(char) * j);
	k = i;
	while (line[i] && line[i] != '>' && line[i] != '<')
	{
		cpy[i - k] = line[i];
		i++;
	}
	cpy[i - k] = '\0';
	return (cpy);
}

/*
	Fonction qui vient extraire les arguments du prompt
*/
char		**args_finder(char *line)
{
	char	**args;
	char	*cpy;
	int		i;

	i = 0;
	while (line[i] == ' ')
		i++;
	while (line[i] == '>' || line[i] == '<')
		i = skip_redirection(line, i);
	while (line[i] != ' ')
		i++;
	cpy = args_copy(line, i);
	args = ft_split(cpy, ' ');
	return(args);
}