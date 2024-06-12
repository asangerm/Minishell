/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:41:47 by nfradet           #+#    #+#             */
/*   Updated: 2024/06/12 17:19:32 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pwd(t_data *data)
{
	if (data->pwd != NULL)
	{
		if (data->old_pwd != NULL)
			free(data->old_pwd);
		data->old_pwd = ft_strdup(data->pwd);
		free(data->pwd);
	}
	data->pwd = getcwd(NULL, 0);
	if (data->pwd == NULL)
	{
		data->pwd = data->old_pwd;
		data->old_pwd = NULL;
	}
}

void	ft_init_data(t_data *data, char **env)
{
	g_last_signal = 0;
	data->ppid = getppid();
	data->old_pwd = NULL;
	data->pwd = NULL;
	data->env = NULL;
	data->prompt = NULL;
	data->paths = NULL;
	data->is_exit = false;
	data->pipes = NULL;
	data->inout_save[READ_END] = dup(STDIN_FILENO);
	data->inout_save[WRITE_END] = dup(STDOUT_FILENO);
	ft_initenv(data, env);
}

void	ft_initenv(t_data *data, char **env)
{
	int			i;
	t_keyval	*tmp;
	t_list		*new;

	new = NULL;
	tmp = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		tmp = extract_var(env[i], true);
		if (tmp && tmp->key)
		{
			new = ft_lstnew(tmp);
			ft_lstadd_back(&(data->env), new);
		}
		i++;
	}
	update_shlvl(data);
}
