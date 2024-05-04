/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:29:25 by marvin            #+#    #+#             */
/*   Updated: 2024/04/26 15:29:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_keyval(void *kv)
{
	t_keyval	*cast;

	cast = (t_keyval *)kv;
	free(cast->key);
	if (cast->val != NULL)
		free(cast->val);
	free(cast);
}

void	ft_handle_errors(char *err_msg)
{
	ft_printf("%s\n", err_msg);
}