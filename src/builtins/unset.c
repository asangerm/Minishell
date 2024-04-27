/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:15:13 by marvin            #+#    #+#             */
/*   Updated: 2024/04/26 17:15:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_node(t_list **head, t_list *node)
{
	t_list	*prev;

	if (node == NULL)
		return;
	if ((*head) == node)
		(*head) = node->next;
	else
	{
		prev = (*head);
		while (prev->next && prev->next != node)
			prev = prev->next;
		prev->next = node->next;
	}
	ft_lstdelone(node, &ft_free_keyval);
}

void	ft_unset(t_data *data, char **arg)
{
	t_list		*key;
	t_keyval	*kv;
	int			i;

	i = 0;
	while (arg && arg[i])
	{
		kv = extract_var(arg[i]);
		key = get_key(data, kv->key);
		if (key != NULL && ft_strncmp(kv->key, "_", ft_strlen(kv->key) != 0))
			del_node(&data->env, get_key(data, arg[i]));
		i++;
	}
}
