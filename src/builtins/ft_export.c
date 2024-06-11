/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:44:38 by nfradet           #+#    #+#             */
/*   Updated: 2024/06/11 17:45:18 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Cherche dans l'environnement la variable 'key'
 * 
 * @param data structure t_data qui contient l'environnement.
 * @param key chaine qui correspond a une variable d'environnement.
 * @return (t_list*) le pointeur vers le noeud de l'env si une var correspond,
 * 					 NULL sinon 
*/
t_list	*get_key(t_data *data, char *key)
{
	t_list	*i;
	char	*str;

	str = NULL;
	i = data->env;
	while (i && key)
	{
		str = ((t_keyval*)i->content)->key;
		if (ft_strncmp(str, key, ft_maxlen(str, key)) == 0)
			return (i);
		i = i->next;
	}
	return (NULL);
}

int	check_exp_args(t_keyval *kv)
{
	int	i;

	i = 0;
	if (ft_isalpha(kv->key[i]) == 0 && kv->key[i] != '_')
		return (1);
	if (kv->key[i] == '\0')
		return (1);
	while (kv->key[i])
	{
		if (ft_isalnum(kv->key[i]) == 0 && kv->key[i] != '_')
		{
			if (kv->key[i] == '+' && i == ((int)ft_strlen(kv->key) - 1))
				return (0);
			return (1);
		}
		i++;
	}
	return (0);
}

char	*cut_plus(char *key)
{
	char	*cpy;
	int		len;
	int		i;

	len = 0;
	while (key[len] && key[len] != '=' && key[len] != '+')
		len++;
	i = 0;
	cpy = malloc(sizeof(char) * len + 1);
	while (key[i] && key[i] != '=' && key[i] != '+')
	{
		cpy[i] = key[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

int	export_arg(t_data *data, char *arg)
{
	char		*var;
	t_list		*key;
	t_keyval	*kv;

	kv = extract_var(arg, true);
	if (check_exp_args(kv) == 1)
		return (ft_free_keyval(kv), 1);
	var = cut_plus(kv->key);
	key = get_key(data, var);
	if (key != NULL )
	{
		if (kv->val != NULL)
		{
			free(((t_keyval *)key->content)->val);
			((t_keyval *)key->content)->val = ft_strdup(kv->val);
		}
		((t_keyval *)key->content)->is_exported = true;
		ft_free_keyval(kv);
	}
	else
		add_var_to_env(data, kv);
	free(var);
	return (0);
}

/**
 * @brief Reproduit le comportement de la commande export en bash
 * 
 * @param data Structure qui contient l'environnement
 * @param args Liste chainee contenant les arguments
 */
void	ft_export(t_data *data, t_string *args)
{
	t_list		*env_cpy;
	t_string	*i;

	if (args == NULL)
	{
		env_cpy = sort_env(data);
		aff_env(env_cpy, 2);
		ft_lstclear(&env_cpy, &ft_free_keyval);
	}
	else
	{
		i = args;
		while (i)
		{
			if (export_arg(data, i->str) == 1)
			{
				aff_err(EXPORT_ERR, ft_strdup(i->str));
				custom_exit(data, 1);
			}
			i = i->next;
		}
	}
}
