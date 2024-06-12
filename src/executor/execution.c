/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:45:15 by nfradet           #+#    #+#             */
/*   Updated: 2024/06/12 17:35:59 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_n_exec(t_data *data, t_prompt *prompt, int i)
{
	if (g_last_signal == 134)
		custom_exit(data, 130);
	g_last_signal = 0;
	ft_handle_var_env(data, prompt);
	if (data->pipes != NULL)
		ft_redirection_pipes(data, i);
	ft_redirection_files(data->files_redir);
	if (ft_exe_builtin(data, prompt->cmd, prompt->args) == 0)
	{
		if (ft_exe_cmd(data, prompt) == 0)
		{
			aff_err(CMD_NOT_FOUND, ft_strdup(prompt->cmd));
			custom_exit(data, 127);
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
int	ft_executor(t_data *data)
{
	pid_t		pid;
	t_prompt	*cpy_prpt;
	int			i;

	ft_create_pipes(data);
	i = 0;
	cpy_prpt = data->prompt;
	while (cpy_prpt)
	{
		signal(SIGQUIT, SIG_IGN);
		data->files_redir = ft_open_files(data, cpy_prpt);
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			ft_redir_n_exec(data, cpy_prpt, i);
			custom_exit(data, EXIT_SUCCESS);
		}
		cpy_prpt = cpy_prpt->next;
		i++;
	}
	routine_pere(data, data->nb_cmd, pid);
	return (1);
}

void	ft_handle_execution(t_data *data)
{
	signal(SIGINT, handle_sigint_cmd);
	if (data->nb_cmd == 1 && ft_is_builtin(data->prompt) == 1)
	{
		g_last_signal = 0;
		data->is_exit = false;
		ft_handle_var_env(data, data->prompt);
		if (g_last_signal != 0)
			return ;
		ft_redirection_files(ft_open_files(data, data->prompt));
		if (g_last_signal == 134)
			g_last_signal = 130;
		if (g_last_signal != 0)
			return ;
		ft_exe_builtin(data, data->prompt->cmd, data->prompt->args);
	}
	else
	{
		g_last_signal = 0;
		data->is_exit = true;
		ft_executor(data);
	}
}
