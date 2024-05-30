/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:35:49 by asangerm          #+#    #+#             */
/*   Updated: 2024/05/30 17:00:38 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_string *args)
{
	int			n;
	t_string	*tmp;

	n = 0;
	tmp = args;
	if (args == NULL)
		return((void)ft_printf("\n"));
	if (ft_strncmp("-n", args->str, 3) == 0)
	{
		n = 1;
		tmp = tmp->next;
	}
	while (tmp)
	{
		if (tmp->type == true)
			ft_printf(" %s", tmp->str);
		else
			ft_printf("%s", tmp->str);
		tmp = tmp->next;
	}
	if (n == 0)
		ft_printf("\n");
	return;
}
