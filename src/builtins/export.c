/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:44:38 by nfradet           #+#    #+#             */
/*   Updated: 2024/04/26 16:56:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * is_sorted
 * @param env l'environnement sous forme de liste chainee
 * @return int 1 si la liste est triee dans l'ordre lexicographie,
 * 0 sinon.
*/
int	is_sorted(t_list *env)
{
	t_list	*j_env;
	char	*s1;
	char	*s2;

	while (env != NULL)
	{
		j_env = env->next;
		while (j_env != NULL)
		{
			s1 = ((t_keyval *)env->content)->key;
			s2 = ((t_keyval *)j_env->content)->key;
			if (ft_strncmp(s1, s2, ft_maxlen(s1, s2)) > 0)
				return (0);
			j_env = j_env->next;
		}
		env = env->next;
	}
	return (1);
}

void	swap(t_list **list)
{
	void	*tmp;

	tmp = (*list)->content;
	if (ft_lstsize(*list) > 1)
	{
		(*list)->content = (*list)->next->content;
		(*list)->next->content = tmp;
	}
}

/**
 * * sort_env
 * @param data structure t_data qui contient l'environnement
 * creer une copie de l'environnement et le trie dans
 * l'ordre lexicographique
 * @return (t_list*) une copie triee de l'environnement 
*/
t_list	*sort_env(t_data *data)
{
	t_list	*sorted;
	t_list	*head;
	char	*actual;
	char	*next;

	sorted = cpy_env(data);
	head = sorted;
	while (is_sorted(head) == 0)
	{
		sorted = head;
		while (sorted != NULL && sorted->next != NULL)
		{
			actual = ((t_keyval *)sorted->content)->key;
			next = ((t_keyval *)sorted->next->content)->key;
			if (ft_strncmp(actual, next, ft_maxlen(actual, next)) > 0)
				swap(&sorted);
			sorted = sorted->next;
		}
	}
	return (head);
}

/**
 * * get_key
 * @param data structure t_data qui contient l'environnement
 * @param key chaine qui correspond a une variable d'environnement
 * Cherche dans l'environnement la variable 'key'
 * @return (t_list*) le pointeur vers le noeud de l'env si une var correspond,
 * 					 NULL sinon 
*/
t_list	*get_key(t_data *data, char *key)
{
	t_list	*i;
	char	*str;

	i = data->env;
	while (i)
	{
		str = ((t_keyval*)i->content)->key;
		if (ft_strncmp(str, key, ft_maxlen(str, key)) == 0)
			return (i);
		i = i->next;
	}
	return (NULL);
}

void	export_arg(t_data *data, char *arg)
{
	t_list		*key;
	t_keyval	*kv;

	kv = extract_var(arg);
	key = get_key(data, kv->key);
	if (key != NULL)
	{
		ft_free_keyval((t_keyval*)key->content);
		key->content = (void*)kv;
	}
	else
	{
		key = ft_lstnew((void*)kv);
		ft_lstadd_back(&data->env, key);
	}
}

void	ft_export(t_data *data, char **arg)
{
	t_list		*env_cpy;
	int			i;

	if (arg == NULL)
	{
		env_cpy = sort_env(data);
		aff_env(env_cpy, 2);
	}
	else
	{
		i = 0;
		while (arg[i])
		{
			export_arg(data, arg[i]);
			i++;
		}
	}
}
