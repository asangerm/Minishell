/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:48:22 by nfradet           #+#    #+#             */
/*   Updated: 2024/06/12 14:32:01 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_all_digit(char *str)
{
	int	i;

	i = 0;
	if (str && str[i] == '-')
		i++;
	while (str && str[i])
	{
		if (ft_isdigit(str[i]) != 1)
			return (0);
		i++;
	}
	return (1);
}

int	ft_strlen_until(char *str, char stop_char)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != stop_char)
		i++;
	return (i);
}

void	update_shlvl(t_data *data)
{
	int			tmp;
	int			new_val;
	char		*val_tmp;
	t_list		*key;
	t_keyval	*kv;

	key = get_key(data, "SHLVL");
	if (key != NULL)
	{
		kv = (t_keyval *)key->content;
		tmp = ft_atoi(kv->val);
		if (kv->val == NULL || ft_all_digit(kv->val) != 1)
			new_val = 1;
		else if (tmp < 0)
			new_val = 0;
		else
			new_val = tmp + 1;
		val_tmp = kv->val;
		kv->val = ft_itoa(new_val);
		if (val_tmp)
			free(val_tmp);
	}
	else
		add_var_to_env(data, extract_var("SHLVL=1", true));
}

t_keyval	*extract_var(char *var, t_bool is_exported)
{
	int			i;
	int			len_until;
	t_keyval	*keyval;

	len_until = ft_strlen_until(var, '=');
	keyval = malloc(sizeof(t_keyval));
	keyval->val = NULL;
	keyval->key = malloc(sizeof(char) * (len_until + 1));
	keyval->is_exported = is_exported;
	if (keyval->key == NULL)
		return (free(keyval), NULL);
	i = 0;
	while (var[i] && var[i] != '=')
	{
		keyval->key[i] = var[i];
		i++;
	}
	keyval->key[i] = '\0';
	if (var[i] && var[i] == '=')
		i++;
	if (ft_strlen(var) - len_until > 0)
		keyval->val = ft_strdup(&var[i]);
	return (keyval);
}
