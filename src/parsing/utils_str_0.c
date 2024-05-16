/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:43:02 by asangerm          #+#    #+#             */
/*   Updated: 2024/05/16 19:15:46 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	lst_new pour un t_string
*/
t_string	*new_str(char *line)
{
	t_string	*new;

	new = malloc(sizeof(*new));
	new->str = line;
	new->next = NULL;
	return (new);
}

/*
	lst_last pour un t_string
*/
t_string	*last_str(t_string **str)
{
	t_string	*new;

	new = *str;
	if (!new)
		return (NULL);
	while (new->next)
		new = new->next;
	return (new);
}

/*
	lst_add_back pour un t_string
*/
void	str_add_back(t_string **str, t_string *new)
{
	t_string	*tmp;

	if (!*str)
	{
		*str = new;
		return ;
	}
	tmp = last_str(str);
	tmp->next = new;
}

/*
	Libère la mémoire d'un t_string
*/
void	free_str(t_string **str)
{
	t_string	*current;
	t_string	*next;

	current = *str;
	while (current)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
	*str = NULL;
}

int	lst_str_len(t_string *str)
{
	int	len;

	len = 0;
	while (str)
	{
		len++;
		str = str->next;
	}
	return (len);
}
