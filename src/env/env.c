/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:10:33 by nfradet           #+#    #+#             */
/*   Updated: 2024/04/15 19:20:46 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen_until(char *str, char stop_char)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != stop_char)
		i++;
	return (i);
}

void	extract_var(t_keyval *keyval, char *var)
{
	int	i;
	int	j;

	keyval->key = malloc(sizeof(char) * (ft_strlen_until(var, '=') + 1));
	keyval->val = malloc(sizeof(char) * (ft_strlen(var) - ft_strlen_until(var, '=')));
	i = 0;
	while (var[i] && var[i] != '=')
	{
		keyval->key[i] = var[i];
		i++;
	}
	if (var[i])
		i++;
	j = 0;
	while (var[i])
	{
		keyval->val[j] = var[i];
		i++;
		j++;
	}
}

void	ft_initenv(t_data *data, char **env)
{
	int			i;
	t_keyval	tmp;
	t_list		*new;

	i = 0;
	new = NULL;
	data->env = NULL;
	while (env[i] != NULL)
	{
		extract_var(&tmp, env[i]);
		new = ft_lstnew((void *)&tmp);
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
