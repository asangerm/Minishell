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
		return ;
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

void	ft_unset(t_data *data, t_string *args)
{
	t_list		*key;
	t_string	*i;

	i = args;
	while (i != NULL)
	{
		key = get_key(data, i->str);
		if (key != NULL && ft_strncmp(i->str, "_", ft_strlen(i->str)) != 0)
			del_node(&data->env, key);
		i = i->next;
	}
}
