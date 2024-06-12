/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:04:27 by nfradet           #+#    #+#             */
/*   Updated: 2024/06/12 14:38:36 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_last_in(t_data *data, t_string *file_in)
{
	int	fd;

	fd = -1;
	if (g_last_signal != 134)
	{
		if (file_in->type)
			fd = ft_heredoc(data, file_in->str);
		else
			fd = open(file_in->str, O_RDONLY);
		if (fd == -1)
		{
			aff_err(NO_SUCH_FILE, ft_strdup(file_in->str));
			return (custom_exit(data, EXIT_FAILURE));
		}
	}
	return (fd);
}

int	ft_open_file_in(t_data *data, t_string *file_in)
{
	int	fd;

	fd = -1;
	if (file_in != NULL)
	{
		while (file_in->next && g_last_signal != 134)
		{
			if (file_in->type)
				fd = ft_heredoc(data, file_in->str);
			else
				fd = open(file_in->str, O_RDONLY);
			if (fd == -1)
			{
				aff_err(NO_SUCH_FILE, ft_strdup(file_in->str));
				return (custom_exit(data, EXIT_FAILURE));
			}
			close(fd);
			fd = -1;
			file_in = file_in->next;
		}
		fd = open_last_in(data, file_in);
	}
	return (fd);
}

int	ft_open_file_out(t_data *data, t_string *file_out)
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
			return (custom_exit(data, EXIT_FAILURE));
	}
	return (fd);
}

t_pipe	ft_open_files(t_data *data, t_prompt *prompt)
{
	t_pipe		files;

	files.fd[READ_END] = ft_open_file_in(data, prompt->file_in);
	files.fd[WRITE_END] = ft_open_file_out(data, prompt->file_out);
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
