/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:08:22 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/04 17:26:41 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strisdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_data *data, t_string *args)
{
	data->is_exit = true;
	ft_putstr_fd("exit ", 2);
	if (args->str && args->next->str)
	{
		last_signal = 1;
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	}
	else if (args->str && ft_strisdigit(args->str) == 0)
	{
		last_signal = 255;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args->str, 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
	else if (args->str)
		last_signal = ft_atoi(args->str);
	else
		last_signal = 0;
}
