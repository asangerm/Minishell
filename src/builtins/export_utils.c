/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:13:43 by nfradet           #+#    #+#             */
/*   Updated: 2024/06/12 14:36:09 by nfradet          ###   ########.fr       */
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

char	*get_value(t_list *env, char *key)
{
	t_list		*i;
	t_keyval	*kv;

	kv = NULL;
	i = env;
	while (i && key)
	{
		kv = ((t_keyval *)i->content);
		if (ft_strncmp(kv->key, key, ft_maxlen(kv->key, key)) == 0)
			return (kv->val);
		i = i->next;
	}
	return (NULL);
}
