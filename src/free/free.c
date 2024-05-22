/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:29:25 by marvin            #+#    #+#             */
/*   Updated: 2024/04/26 15:29:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_keyval(void *kv)
{
	t_keyval	*cast;

	cast = (t_keyval *)kv;
	free(cast->key);
	if (cast->val != NULL)
		free(cast->val);
	free(cast);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
	{
		free(tab[i]);
		free(tab);
	}
}

void	ft_free_data(t_data *data)
{
	if (data->pipes != NULL)
		free(data->pipes);
	ft_free_tab(data->paths);
	ft_lstclear(&data->env, &ft_free_keyval);
	free(data->pwd);
}

int	builtins_err_handler(char *err_msg, char *variable)
{
	if (variable != NULL)
		ft_printf(err_msg, variable);
	else
		ft_printf(err_msg);
	return (1);
}

void	var_display(t_list **var)
{
	t_list		*tmp;
	t_keyval	*kv;
	int			j;

	if (*var)
	{
		j = 0;
		tmp = *var;
		while (tmp)
		{
			kv = (t_keyval *)tmp->content;
			ft_printf("	Variable number %d =\n		key = #%s#\n		val = #%s#\n", j, kv->key, kv->val);
			j++;
			tmp = tmp->next;
		}
	}
	else
		ft_printf("	Variable = >%s<\n", NULL);
}