/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:13:44 by nfradet           #+#    #+#             */
/*   Updated: 2024/06/12 14:38:05 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	custom_exit(t_data *data, int status)
{
	if (data->is_exit == true)
	{
		ft_free_data(data);
		exit(status);
	}
	else
		g_last_signal = status;
	return (-1);
}

int	is_hd_input_ok(char *line, char *limiter)
{
	if (g_last_signal == 134)
		return (1);
	if (line == NULL)
	{
		aff_err(HD_ERR, ft_strdup(limiter));
		return (1);
	}
	else if (strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}

void	handle_sigint_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		close(STDIN_FILENO);
		g_last_signal = 134;
	}
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
	signal(SIGINT, handle_sigint_cmd);
	close(fd[WRITE_END]);
	return (fd[READ_END]);
}
