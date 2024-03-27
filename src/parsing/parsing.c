/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:50:16 by nfradet           #+#    #+#             */
/*   Updated: 2024/03/27 20:25:30 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_arg(char *arg, t_parse *parsed)
{
	int	i;

	i = 0;
	parsed->parsed_line = malloc(sizeof(char) * (ft_strlen(arg) + 1));
	while (arg[i])
	{
		parsed->parsed_line[i] = arg[i];
		i++;
	}
	parsed->parsed_line[i] = '\0';
}

void	parse_cmd(char *line, t_parse *parsed)
{
	int	i;

	i = 0;
	while (line[i] != ' ')
		i++;
	parsed->cmd = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (line[i] != ' ')
	{
		parsed->cmd[i] = line[i];
		i++;
	}
	parsed->cmd[i] = '\0';
	parse_arg(&line[i], parsed);
}

void	parse_line(char *line)
{
	t_parse	parsed;
	
	parse_cmd(line, &parsed);	
}
