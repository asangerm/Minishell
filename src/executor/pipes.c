/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:05:16 by nfradet           #+#    #+#             */
/*   Updated: 2024/05/23 13:36:11 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_create_pipes(t_data *data)
{
	int		i;

	if (data->nb_cmd == 1)
		data->pipes = NULL;
	else
	{
		data->pipes = malloc(sizeof(t_pipe) * (data->nb_cmd - 1));
		i = 0;
		while (i < data->nb_cmd - 1)
		{
			if (pipe(data->pipes[i].fd) == -1)
				exit(EXIT_FAILURE);
			i++;
		}
	}
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

void	ft_redirection_pipes(t_data *data, int i)
{
	if (i == 0)
	{
		close_pipes_excpt(data->pipes, data->nb_cmd - 1, i, -1);
		close(data->pipes[i].fd[0]);
		dup2(data->pipes[i].fd[1], STDOUT_FILENO);
		close(data->pipes[i].fd[1]);
	}
	else if (i == data->nb_cmd - 1)
	{
		close_pipes_excpt(data->pipes, data->nb_cmd - 1, i - 1, -1);
		close(data->pipes[i - 1].fd[1]);
		dup2(data->pipes[i - 1].fd[0], STDIN_FILENO);
		close(data->pipes[i - 1].fd[0]);
	}
	else
	{
		close_pipes_excpt(data->pipes, data->nb_cmd - 1, i, i - 1);
		close(data->pipes[i - 1].fd[1]);
		dup2(data->pipes[i - 1].fd[0], STDIN_FILENO);
		close(data->pipes[i - 1].fd[0]);
		close(data->pipes[i].fd[0]);
		dup2(data->pipes[i].fd[1], STDOUT_FILENO);
		close(data->pipes[i].fd[1]);
	}
}

char	*get_path(t_data *data, char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	while (data->paths && data->paths[i])
	{
		path = check_path(data->paths[i], cmd);
		if (path != NULL)
			return (path);
		i++;
	}
	return (NULL);
}

int	ft_exe_cmd(t_data *data, t_prompt *prompt)
{
	char	**cmd;
	char	**env;
	char	*path;
	t_list	*tmp;

	data->paths = NULL;
	env = ft_lst_to_tab(data->env);
	cmd = ft_cmd_to_tab(prompt);
	tmp = get_key(data, "PATH");
	if (tmp != NULL)
	{
		ft_free_tab(data->paths);
		data->paths = ft_split(((t_keyval*)tmp->content)->val, ':');
	}
	path = get_path(data, prompt->cmd);
	if (path != NULL)
	{
		if (execve(path, cmd, env) == -1)
			return (1);
	}
	ft_free_tab(cmd);
	ft_free_tab(env);
	return (0);
}
