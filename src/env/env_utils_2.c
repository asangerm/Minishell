/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:48:22 by nfradet           #+#    #+#             */
/*   Updated: 2024/05/31 13:40:01 by nfradet          ###   ########.fr       */
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
		if (ft_all_digit(kv->val) != 1)
			new_val = 1;
		else if (tmp < 0)
			new_val = 0;
		else
			new_val = tmp + 1;
		val_tmp = kv->val;
		kv->val = ft_itoa(new_val);
		free(val_tmp);
	}
	else
		add_var_to_env(data, extract_var("SHLVL=1"));
}
