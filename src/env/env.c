/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:10:33 by nfradet           #+#    #+#             */
/*   Updated: 2024/04/30 13:44:35 by nfradet          ###   ########.fr       */
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
	int			len_until;
	t_keyval	*keyval;

	len_until = ft_strlen_until(var, '=');
	keyval = malloc(sizeof(t_keyval));
	keyval->val = NULL;
	keyval->key = malloc(sizeof(char) * (len_until + 1));
	i = 0;
	while (var[i] && var[i] != '=')
	{
		keyval->key[i] = var[i];
		i++;
	}
	if (var[i] && var[i + 1] == '\"')
		i++;
	if (ft_strlen(var) - len_until > 0)
		keyval->val = double_quote(var, &i);
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
