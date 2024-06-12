/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:10:33 by nfradet           #+#    #+#             */
/*   Updated: 2024/06/12 14:42:48 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	modify_var(t_keyval *kv, t_list *key)
{
	int			len;
	t_keyval	*old_key;
	char		*new_val;

	old_key = ((t_keyval *)key->content);
	len = ft_strlen(old_key->val) + ft_strlen(kv->val);
	if (kv->key[ft_strlen(kv->key) - 1] == '+')
	{
		new_val = malloc(sizeof(char) * (len + 1));
		ft_memcpy(new_val, old_key->val, ft_strlen(old_key->val));
		new_val[ft_strlen(old_key->val)] = '\0';
		ft_strlcat(new_val, kv->val, len + 1);
		free(((t_keyval *)key->content)->val);
		((t_keyval *)key->content)->val = new_val;
		ft_free_keyval(kv);
	}
	else
	{
		ft_free_keyval((t_keyval *)key->content);
		key->content = (void *)kv;
	}
}

void	add_var_to_env(t_data *data, t_keyval *kv)
{
	t_list	*key;
	char	*var;

	var = cut_plus(kv->key);
	key = get_key(data, var);
	if (key != NULL && kv->val != NULL)
	{
		kv->is_exported = ((t_keyval *)key->content)->is_exported;
		modify_var(kv, key);
		free(var);
	}
	else if (key == NULL)
	{
		free(kv->key);
		kv->key = var;
		key = ft_lstnew((void *)kv);
		ft_lstadd_back(&data->env, key);
	}
}

int	ft_handle_var_env(t_data *data, t_prompt *prompt)
{
	t_prompt	*tmp;
	t_keyval	*kv;
	t_list		*var;

	tmp = prompt;
	while (tmp != NULL)
	{
		var = tmp->var;
		while (var != NULL)
		{
			kv = cpy_keyval((t_keyval *)var->content);
			if (check_exp_args(kv) == 1)
			{
				aff_err(CMD_NOT_FOUND, kv_to_str(kv));
				ft_free_keyval(kv);
				return (custom_exit(data, 127));
			}
			add_var_to_env(data, kv);
			var = var->next;
		}
		tmp = tmp->next;
	}
	return (0);
}
