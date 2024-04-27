/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:10:33 by nfradet           #+#    #+#             */
/*   Updated: 2024/04/26 16:15:57 by marvin           ###   ########.fr       */
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

t_keyval	*extract_var(char *var)
{
	int			i;
	int			j;
	t_keyval	*keyval;

	keyval = malloc(sizeof(t_keyval));
	keyval->val = NULL;
	keyval->key = malloc(sizeof(char) * (ft_strlen_until(var, '=') + 1));
	if (ft_strlen(var) - ft_strlen_until(var, '=') > 0)
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
	return (keyval);
}

void	ft_initenv(t_data *data, char **env)
{
	int			i;
	t_keyval	*tmp;
	t_list		*new;

	i = 0;
	new = NULL;
	data->env = NULL;
	while (env[i] != NULL)
	{
		tmp = extract_var(env[i]);
		new = ft_lstnew(tmp);
		ft_lstadd_back(&(data->env), new);
		i++;
	}
}
