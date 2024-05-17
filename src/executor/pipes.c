/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:05:16 by nfradet           #+#    #+#             */
/*   Updated: 2024/05/17 14:55:54 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe	*ft_create_pipes(t_data *data)
{
	t_pipe	*pipes;
	int		i;

	pipes = malloc(sizeof(t_pipe) * (data->nb_cmd - 1));
	i = 0;
	while (i < data->nb_cmd - 1)
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

int	ft_exe_cmd(t_data *data, t_prompt *prompt)
{
	char	**cmd;
	char	**env;
	char	*path;
	t_list	*tmp;
	int		i;

	env = ft_lst_to_tab(data->env);
	cmd = ft_cmd_to_tab(prompt);
	tmp = get_key(data, "PATH");
	if (tmp != NULL)
		data->paths = ft_split(((t_keyval*)tmp->content)->val, ':');
	else
		return (0);
	i = 0;
	while (data->paths[i])
	{
		path = check_path(data->paths[i], prompt->cmd);
		if (path != NULL)
		{
			execve(path, cmd, env);
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief creer les pipes, et creer un processus fils pour chaque commandes
 * chaque fils effectue les redirections necessaires des pipes 
 * puis des fichiers
 * ensuite, chaque fils va executer la commande correspondante
 * 
 * @param data struct t_data contenant l'environnement
 * @param prompt struct t_prompt contenant le prompt parse
 */
int	ft_handle_pipes(t_data *data, t_prompt *prompt)
{
	pid_t		pid;
	t_pipe		*pipes;
	int			i;

	pipes = ft_create_pipes(data);
	i = 0;
	while (prompt)
	{
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			ft_handle_var_env(data, prompt);
			ft_redirection_pipes(data, pipes, i);
			ft_redirection_files(ft_open_files(prompt));
			if (ft_exe_builtin(data, prompt->cmd, prompt->args) == 0)
				ft_exe_cmd(data, prompt);
			return (0);
		}
		prompt = prompt->next;
		i++;
	}
	routine_pere(pipes, data->nb_cmd);
	return (1);
}

void	ft_exec_no_pipe(t_data *data, t_prompt *prompt)
{
	ft_handle_var_env(data, prompt);
	ft_redirection_files(ft_open_files(prompt));
	if (prompt->cmd != NULL)
	{
		if (ft_exe_builtin(data, prompt->cmd, prompt->args) == 0)
				ft_exe_cmd(data, prompt);
	}
}
