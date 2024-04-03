/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:08:12 by asangerm          #+#    #+#             */
/*   Updated: 2024/04/03 17:22:19 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*space_cutter(char *line)
{
	int		i;
	int		j;
	int		count;
	char	*newline;

	i = 0;
	while(line[i])
	{
		if (line[i] == '|' && i != 0 && line[i-1] == ' ')
			count--;
		if (line[i] == '|' && line[i+1] == ' ')
			count--;
		i++;
		count++;
	}
	printf("count = %d, i = %d\n", count, i);
	newline = malloc(sizeof(char) * count);
	i = 0;
	j = 0;
	while(line[j])
	{
		if (line[j] == ' ' && i != 0 && (line[j+1] == '|' || line[j-1] == '|'))
			j++;
		else
		{
			newline[i] = line[j];
			i++;
			j++;
		}
	}
	newline[i] = '\0';
	printf("new = %s\n", newline);
	return(newline);
}

void	display_parsing(t_prompt *prompt)
{
	int	i;

	i = 0;
	while (prompt[i].cmd != NULL)
	{
		ft_printf("Prompt %d:\n",i);
		ft_printf("	cmd:%s\n", prompt[i].cmd);
		ft_printf("	args:%s\n", prompt[i].args);
		i++;
	}
}

char *extract_cmd(char *line, int len)
{
	char	*cmd;
	int		i;

	cmd = malloc(sizeof(char) * (len + 1));
	i = 0;
	while(i < len)
	{
		cmd[i] = line[i];
		i++;
	}
	cmd[i] = '\0';
	return (cmd);
}

char *extract_args(char *line, int len)
{
	char	*args;
	int		i;

	if (line[len] == ' ')
	{
		args = malloc(sizeof(char) * (ft_strlen(line) - len));
		len++;
	}
	else
		args = malloc(sizeof(char) * (ft_strlen(line) - len + 1));
	i = len;
	while (line[i])
	{
		args[i - len] = line[i];
		i++;
	}
	args[i - len] = '\0';
	return (args);
}

int	cmd_len(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' && i != 0)
			return (i);
		i++;
	}
	return (i);
}

int	prompt_count(char **parsed_line_pipe)
{
	int	i;

	i = 0;
	while (parsed_line_pipe[i])
		i++;
	return (i);
}

t_prompt *parse_prompt(char **parsed_line_pipe)
{
	t_prompt	*parsed_prompt;
	int			count;
	int			i;
	int			len;

	count =  prompt_count(parsed_line_pipe);
	parsed_prompt = malloc(sizeof(t_prompt) * count);
	i = 0;
	while (i < count)
	{
		len = cmd_len(parsed_line_pipe[i]);
		parsed_prompt[i].cmd = extract_cmd(parsed_line_pipe[i], len);
		parsed_prompt[i].args =  extract_args(parsed_line_pipe[i], len);
		i++;
	}
	parsed_prompt[i].cmd = NULL;
	parsed_prompt[i].args = NULL;
	return (parsed_prompt);
}

char **parse_pipe(char *line)
{
	char	**parsed_line;

	parsed_line = ft_split(line, '|');
	return (parsed_line);
}

void	parse(char *line)
{
	char		**parsed_line_pipe;
	t_prompt	*parsed_prompt;
	char		*newline;

	newline = space_cutter(line);
	parsed_line_pipe = parse_pipe(newline);
	parsed_prompt = parse_prompt(parsed_line_pipe);
	display_parsing(parsed_prompt);
}