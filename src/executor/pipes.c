/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:05:16 by nfradet           #+#    #+#             */
/*   Updated: 2024/05/20 21:27:06 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe	*ft_create_pipes(t_data *data)
{
	t_pipe	*pipes;
	int		i;

	if (data->nb_cmd == 1)
		return (NULL);
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

char	*get_path(t_data *data, char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	// ft_printf("%s : %d\n",cmd, access(cmd, F_OK | X_OK));
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

	env = ft_lst_to_tab(data->env);
	cmd = ft_cmd_to_tab(prompt);
	tmp = get_key(data, "PATH");
	if (tmp != NULL)
		data->paths = ft_split(((t_keyval*)tmp->content)->val, ':');
	path = get_path(data, prompt->cmd);
	// ft_printf("%s\n", path);
	if (path != NULL)
	{
		free_chain(&prompt);
		ft_free_data(data);
		if (execve(path, cmd, env) == -1)
			return (1);
	}
	return (0);
}

int	ft_redir_n_exec(t_data *data, t_prompt *prompt, t_pipe *pipes, int i)
{
	ft_handle_var_env(data, prompt);
	if (pipes != NULL)
	{
		ft_redirection_pipes(data, pipes, i);
		free(pipes);
	}
	ft_redirection_files(ft_open_files(prompt));
	if (ft_exe_builtin(data, prompt->cmd, prompt->args) == 0)
	{
		ft_exe_cmd(data, prompt);
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
int	ft_executor(t_data *data, t_prompt *prompt)
{
	pid_t		pid;
	t_pipe		*pipes;
	int			i;

	data->inout_save[0] = dup(STDIN_FILENO);
	data->inout_save[1] = dup(STDOUT_FILENO);
	pipes = ft_create_pipes(data);
	i = 0;
	while (prompt)
	{
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			ft_redir_n_exec(data, prompt, pipes, i);
			ft_free_data(data);
			free_chain(&prompt);
			exit(0);
		}
		prompt = prompt->next;
		i++;
	}
	routine_pere(data, pipes, data->nb_cmd);
	return (1);
}
