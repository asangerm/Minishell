/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:04:27 by nfradet           #+#    #+#             */
/*   Updated: 2024/06/03 19:40:42 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		close(STDIN_FILENO);
		last_signal = 134;
	}
}

int	is_hd_input_ok(char *line, char *limiter)
{
	if (last_signal == 134)
		return (1);
	if (line == NULL)
	{
		builtins_err_handler(HD_ERR, ft_strdup(limiter));
		return (1);
	}
	else if (strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}

int	ft_heredoc(t_data *data, char *limiter)
{
	int		fd[2];
	char	*line;

	(void)data;
	if (pipe(fd) == -1)
		return (-1);
	while (1)
	{
		signal(SIGINT, handle_sigint_heredoc);
		line = readline("> ");
		if (is_hd_input_ok(line, limiter) == 1)
			break ;
		ft_putstr_fd(line, fd[WRITE_END]);
		ft_putstr_fd("\n", fd[WRITE_END]);
		free(line);
	}
	close(fd[WRITE_END]);
	return (fd[READ_END]);
}

int	open_last_in(t_data *data, t_string *file_in)
{
	int	fd;

	fd = -1;
	if (last_signal != 134)
	{
		if (file_in->type)
			fd = ft_heredoc(data, file_in->str);
		else
			fd = open(file_in->str, O_RDONLY);
		if (fd == -1)
		{
			builtins_err_handler(NO_SUCH_FILE, ft_strdup(file_in->str));
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
		while (file_in->next && last_signal != 134)
		{
			if (file_in->type)
				fd = ft_heredoc(data, file_in->str);
			else
				fd = open(file_in->str, O_RDONLY);
			if (fd == -1)
			{
				builtins_err_handler(NO_SUCH_FILE, ft_strdup(file_in->str));
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

