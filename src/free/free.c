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

int	builtins_err_handler(char *err_msg, char *variable)
{
	if (variable != NULL)
		ft_printf(err_msg, variable);
	else
		ft_printf(err_msg);
	return (1);
}