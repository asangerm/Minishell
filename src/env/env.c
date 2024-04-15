/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:10:33 by nfradet           #+#    #+#             */
/*   Updated: 2024/04/15 16:41:44 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_initenv(t_data *data, char **env)
{
	int		i;
	char	*tmp;
	t_list	*new;

	i = 0;
	new = NULL;
	data->env = NULL;
	while (env[i] != NULL)
	{
		tmp = ft_strdup(env[i]);
		new = ft_lstnew((void *)tmp);
		ft_lstadd_back(&(data->env), new);
		i++;
	}
}

char	*ft_getenv(t_data *data, char *arg)
{
	t_list	*lst;
	
	lst = data->env;
	while (lst)
	{
		if (find_var(data->env->content, arg) == 0)
			return ((char *)data->env->content + ft_strlen(arg) + 1);
		lst = lst->next;
	}
	return (NULL);
}
