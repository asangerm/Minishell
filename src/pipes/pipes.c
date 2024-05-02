/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:05:16 by nfradet           #+#    #+#             */
/*   Updated: 2024/05/02 16:42:17 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe	*ft_create_pipes(t_data *data, t_prompt *prompt)
{
	t_pipe	*pipes;
	int		len;
	int		i;

	len = 0;
	while (prompt)
		len++;
	data->nb_cmd = len;
	pipes = malloc(sizeof(t_pipe) * (len - 1));
	i = 0;
	while (i < len - 1)
	{
		if (pipe(pipes[i].fd) == -1)
			exit(EXIT_FAILURE);
		i++;
	}
	return (pipes);
}

void	close_pipes_excpt(t_pipe *pipes, int nb_pipes, int e1, int e2)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		if (i != e1 && i != e2)
		{
			close(pipes[i].fd[0]);
			close(pipes[i].fd[1]);
		}
		i++;
	}
}

void	ft_redirection_pipes(t_data *data, t_pipe *pipe, int i)
{
	if (i == 0)
	{
		close_pipes_excpt(pipe, data->nb_cmd - 1, i, -1);
		close(pipe[i].fd[0]);
		dup2(pipe[i].fd[1], STDOUT_FILENO);
		close(pipe[i].fd[1]);
	}
	else if (i == data->nb_cmd - 1)
	{
		close_pipes_excpt(pipe, data->nb_cmd - 1, i - 1, -1);
		close(pipe[i - 1].fd[1]);
		dup2(pipe[i - 1].fd[0], STDIN_FILENO);
		close(pipe[i - 1].fd[0]);
	}
	else
	{
		close_pipes_excpt(pipe, data->nb_cmd - 1, i, i - 1);
		close(pipe[i - 1].fd[1]);
		dup2(pipe[i - 1].fd[0], STDIN_FILENO);
		close(pipe[i - 1].fd[0]);
		close(pipe[i].fd[0]);
		dup2(pipe[i].fd[1], STDOUT_FILENO);
		close(pipe[i].fd[1]);
	}
}

void	ft_handle_pipes(t_data *data, t_prompt *prompt)
{
	t_prompt	*ind;
	pid_t		pid;
	t_pipe		*pipes;
	int			i;

	pipes = ft_create_pipes(data, prompt);
	ind = prompt;
	i = 0;
	while (ind)
	{
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			ft_redirection_pipes(data, pipes, i);
			ft_redirection_files(ft_open_files(prompt));
			break ;
		}
		ind = ind->next;
		i++;
	}
}
