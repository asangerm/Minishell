/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:10:33 by nfradet           #+#    #+#             */
/*   Updated: 2024/05/23 17:14:02 by nfradet          ###   ########.fr       */
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
	if (keyval->key == NULL)
		return (free(keyval), NULL);
	i = 0;
	while (var[i] && var[i] != '=')
	{
		keyval->key[i] = var[i];
		i++;
	}
	keyval->key[i] = '\0';
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
	tmp = NULL;
	data->env = NULL;
	data->paths = NULL;
	while (env[i] != NULL)
	{
		tmp = extract_var(env[i]);
		tmp->is_exported = true;
		if (tmp && tmp->key)
		{
			new = ft_lstnew(tmp);
			ft_lstadd_back(&(data->env), new);
		}
		i++;
	}
}

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
	}
	else
	{
		ft_free_keyval((t_keyval*)key->content);
		key->content = (void*)kv;
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
		modify_var(kv, key);
		free(var);
	}
	else if (key == NULL)
	{
		free(kv->key);
		kv->key = var;
		key = ft_lstnew((void*)kv);
		ft_lstadd_back(&data->env, key);
	}
}

void	ft_handle_var_env(t_data *data, t_prompt *prompt)
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
			kv->is_exported = ((t_keyval *)var->content)->is_exported;
			add_var_to_env(data, kv);
			var = var->next;
		}
		tmp = tmp->next;
	}
}
