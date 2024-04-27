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

void	del_node(t_list *head, t_list *node)
{
	t_list	*prev;

	while (head->next && head->next != node)
	{
		head = head->next;
	}
		ft_printf("egal ? %d\n", head->next == node);
	prev = node;
	prev->next = node->next;
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
		if (key != NULL)
		{
			ft_free_keyval(key->content);
			key->content = (void*)kv;
		}
		else
		{
			key = ft_lstnew((void*)kv);
			ft_lstadd_back(&data->env, key);
		}
		i++;
	}
}
