/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:04:27 by nfradet           #+#    #+#             */
/*   Updated: 2024/05/28 15:16:06 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_heredoc(t_data *data, char *limiter)
{
	int		fd[2];
	char	*lim;
	char	*line;

	if (pipe(fd) == -1)
		return (-1);
	lim = ft_strjoin(limiter, "\n");
	while (1)
	{
		ft_putstr_fd("> ", data->inout_save[WRITE_END]);
		line = get_next_line(data->inout_save[READ_END]);
		if (strncmp(line, lim, ft_strlen(lim)) == 0)
			break ;
		ft_putstr_fd(line, fd[WRITE_END]);
		free(line);
	}
	free(line);
	free(lim);
	get_next_line(-1);
	close(fd[WRITE_END]);
	return (fd[READ_END]);
}

int	ft_open_file_in(t_data *data, t_string *file_in)
{
	int	fd;

	fd = -1;
	if (file_in != NULL)
	{
		while (file_in->next)
		{
			if (file_in->type)
				fd = ft_heredoc(data, file_in->str);
			else
				fd = open(file_in->str, O_RDONLY);
			if (fd == -1)
				exit(EXIT_FAILURE);
			close(fd);
			fd = -1;
			file_in = file_in->next;
		}
		if (file_in->type)
			fd = ft_heredoc(data, file_in->str);
		else
			fd = open(file_in->str, O_RDONLY);
		if (fd == -1)
			exit(EXIT_FAILURE);
	}
	return (fd);
}

int	ft_open_file_out(t_string *file_out)
{
	int	fd;

	fd = -1;
	if (file_out != NULL)
	{
		while (file_out->next)
		{
			if (file_out->type)
				fd = open(file_out->str, O_WRONLY | O_CREAT | O_APPEND, 0666);
			else
				fd = open(file_out->str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			close(fd);
			file_out = file_out->next;
		}
		if (file_out->type)
			fd = open(file_out->str, O_WRONLY | O_CREAT | O_APPEND, 0666);
		else
			fd = open(file_out->str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
			exit(EXIT_FAILURE);
	}
	return (fd);
}

t_pipe	ft_open_files(t_data *data, t_prompt *prompt)
{
	t_pipe		files;

	files.fd[READ_END] = ft_open_file_in(data, prompt->file_in);
	files.fd[WRITE_END] = ft_open_file_out(prompt->file_out);
	return (files);
}

void	ft_redirection_files(t_pipe files)
{
	if (files.fd[READ_END] != -1)
	{
		dup2(files.fd[READ_END], STDIN_FILENO);
		close(files.fd[READ_END]);
	}
	if (files.fd[WRITE_END] != -1)
	{
		dup2(files.fd[WRITE_END], STDOUT_FILENO);
		close(files.fd[WRITE_END]);
	}

}

