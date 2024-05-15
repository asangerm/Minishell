/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:34:55 by nfradet           #+#    #+#             */
/*   Updated: 2024/05/15 15:13:53 by nfradet          ###   ########.fr       */
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
	return (NULL);
}

char	**ft_lst_to_tab(t_list *env)
{
	char	*tmp;
	char	**tab;
	int		i;

	i = 0;
	tab = malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	while (i < ft_lstsize(env))
	{
		tmp = ft_strjoin(((t_keyval *)env->content)->key, "=");
		tab[i] = ft_strjoin(tmp, ((t_keyval *)env->content)->val);
		free(tmp);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	**ft_cmd_to_tab(t_prompt *prompt)
{
	t_string	*args;
	char		**tab;
	int			i;

	args = prompt->args;
	tab = malloc(sizeof(char *) * (lst_str_len(prompt->args) + 2));
	tab[0] = prompt->cmd;
	i = 1;
	while (args)
	{
		tab[i] = args->str;
		args = args->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

void	routine_pere(t_pipe *pipes, int nb_fork)
{
	int		i;
	int		status;

	close_pipes_excpt(pipes, nb_fork - 1, -1, -1);
	free(pipes);
	i = 0;
	while (i < nb_fork)
	{
		waitpid(-1, &status, 0);
		i++;
	}
}

void	ft_init_nb_cmd(t_data *data, t_prompt * prompt)
{
	int	len;

	len = 0;
	while (prompt)
	{
		len++;
		prompt = prompt->next;
	}
	data->nb_cmd = len;
}