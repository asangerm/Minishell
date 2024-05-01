/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:44:38 by nfradet           #+#    #+#             */
/*   Updated: 2024/04/30 15:39:27 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
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
 * @brief creer une copie de l'environnement et le trie dans
 * l'ordre lexicographique
 * 
 * @param data structure t_data qui contient l'environnement
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
	(void)key;

	str = NULL;
	i = data->env;
		ft_printf("%s\n", key);
	while (i && key)
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
	}
	else
	{
		i = args;
		while (i)
		{
			export_arg(data, i->str);
			i = i->next;
		}
	}
}
