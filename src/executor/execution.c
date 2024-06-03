/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:45:15 by nfradet           #+#    #+#             */
/*   Updated: 2024/06/03 18:29:46 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_n_exec(t_data *data, t_prompt *prompt, int i)
{
	if (last_signal == 134)
		exit(130);
	last_signal = 0;
	ft_handle_var_env(data, prompt);
	if (data->pipes != NULL)
		ft_redirection_pipes(data, i);
	ft_redirection_files(data->files_redir);
	if (ft_exe_builtin(data, prompt->cmd, prompt->args) == 0)
	{
		if (ft_exe_cmd(data, prompt) == 0)
		{
			builtins_err_handler(CMD_NOT_FOUND, ft_strdup(prompt->cmd));
			exit(127);
		}
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
	t_prompt	*cpy_prpt;
	int			i;

	ft_create_pipes(data);
	i = 0;
	cpy_prpt = prompt;
	while (cpy_prpt)
	{
		data->files_redir = ft_open_files(data, cpy_prpt);
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			ft_redir_n_exec(data, cpy_prpt, i);
			ft_free_data(data);
			free_chain(&prompt);
			exit(EXIT_SUCCESS);
		}
		cpy_prpt = cpy_prpt->next;
		i++;
	}
	routine_pere(data, data->nb_cmd, pid);
	return (1);
}

void	ft_handle_execution(t_data *data, t_prompt *prompt)
{
	signal(SIGINT, handle_sigint_cmd);
	if (data->nb_cmd == 1 && ft_is_builtin(prompt) == 1)
	{
		last_signal = 0;
		data->is_exit = false;
		ft_handle_var_env(data, prompt);
		ft_redirection_files(ft_open_files(data, prompt));
		signal(SIGINT, handle_sigint_cmd);
		if (last_signal == 134)
		{
			last_signal = 130;
			return ;
		}
		if (last_signal != 0)
			return ;
		ft_exe_builtin(data, prompt->cmd, prompt->args);
	}
	else
	{
		data->is_exit = true;
		ft_executor(data, prompt);
	}
}
