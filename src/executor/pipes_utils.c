/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:34:55 by nfradet           #+#    #+#             */
/*   Updated: 2024/06/12 17:11:38 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_path(char *path, char *cmd)
{
	char	*join;
	char	*tmp;

	tmp = ft_strjoin("/", cmd);
	join = ft_strjoin(path, tmp);
	free(tmp);
	if (access(join, F_OK | X_OK) == 0)
		return (join);
	free(join);
	return (NULL);
}

char	**lst_to_tab(t_list *env)
{
	char	*tmp;
	char	**tab;
	t_list	*lst;
	int		i;

	i = 0;
	lst = env;
	tab = malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	while (lst && i < ft_lstsize(env))
	{
		tmp = ft_strjoin(((t_keyval *)lst->content)->key, "=");
		tab[i] = ft_strjoin(tmp, ((t_keyval *)lst->content)->val);
		free(tmp);
		lst = lst->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	**cmd_to_tab(t_prompt *prompt)
{
	t_string	*arg;
	char		**tab;
	int			i;

	arg = prompt->args;
	tab = malloc(sizeof(char *) * (lst_str_len(arg) + 2));
	tab[0] = ft_strdup(prompt->cmd);
	i = 1;
	while (arg != NULL && i < lst_str_len(prompt->args) + 2)
	{
		tab[i] = ft_strdup(arg->str);
		arg = arg->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

void	routine_pere(t_data *data, int nb_fork, pid_t last_pid)
{
	int		i;
	int		status;

	close_pipes_excpt(data->pipes, nb_fork - 1, -1, -1);
	free(data->pipes);
	data->pipes = NULL;
	i = 0;
	waitpid(last_pid, &status, 0);
	if (WIFEXITED(status))
		g_last_signal = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_last_signal = 128 + WTERMSIG(status);
	while (i < nb_fork - 1)
	{
		waitpid(-1, &status, 0);
		i++;
	}
}

void	ft_init_nb_cmd(t_data *data, t_prompt *prompt)
{
	int			len;
	t_prompt	*tmp;

	len = 0;
	tmp = prompt;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	data->nb_cmd = len;
}
