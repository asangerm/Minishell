/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:04:27 by nfradet           #+#    #+#             */
/*   Updated: 2024/05/26 14:56:19 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_file_in(t_string *file_in)
{
	int	fd;

	fd = -1;
	if (file_in != NULL)
	{
		while (file_in->next)
		{
			fd = open(file_in->str, O_RDONLY);
			if (fd == -1)
				exit(EXIT_FAILURE);
			close(fd);
			file_in = file_in->next;
		}
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
			if (file_out->type == 2)
				fd = open(file_out->str, O_WRONLY | O_CREAT | O_APPEND, 0666);
			else
				fd = open(file_out->str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			close(fd);
			file_out = file_out->next;
		}
		if (file_out->type == 2)
			fd = open(file_out->str, O_WRONLY | O_CREAT | O_APPEND, 0666);
		else
			fd = open(file_out->str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
			exit(EXIT_FAILURE);
	}
	return (fd);
}

t_pipe	ft_open_files(t_prompt *prompt)
{
	t_pipe		files;

	files.fd[0] = ft_open_file_in(prompt->file_in);
	files.fd[1] = ft_open_file_out(prompt->file_out);
	return (files);
}

void	ft_redirection_files(t_pipe files)
{
	if (files.fd[0] != -1)
	{
		dup2(files.fd[0], STDIN_FILENO);
		close(files.fd[0]);
	}
	else if (files.fd[1] != -1)
	{
		dup2(files.fd[1], STDOUT_FILENO);
		close(files.fd[1]);
	}
}

