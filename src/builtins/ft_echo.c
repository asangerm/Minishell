/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:35:49 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/12 14:33:55 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	option_check(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '-')
		return (0);
	i++;
	while (str[i] && str[i] == 'n')
	{
		i++;
	}
	if (str[i] == '\0')
		return (1);
	return (0);
}

void	ft_echo(t_string *args)
{
	int			n;
	t_string	*tmp;

	n = 0;
	tmp = args;
	if (args == NULL)
		return ((void )ft_printf("\n"));
	while (tmp && option_check(tmp->str))
	{
		n = 1;
		tmp = tmp->next;
	}
	while (tmp)
	{
		ft_printf("%s", tmp->str);
		if (tmp->next)
			ft_printf(" ");
		tmp = tmp->next;
	}
	if (n == 0)
		ft_printf("\n");
	return ;
}
