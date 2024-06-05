/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:08:22 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/05 16:10:26 by nfradet          ###   ########.fr       */
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
	if (data->is_exit == false)
		ft_putstr_fd("exit\n", 2);
	data->is_exit = true;
	if (args && args->next)
	{
		last_signal = 1;
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	}
	else if (args && ft_strisdigit(args->str) == 0)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args->str, 2);
		ft_putendl_fd(": numeric argument required", 2);
		custom_exit(data, 2);
	}
	else if (args)
		custom_exit(data, ft_atoi(args->str));
	else
		custom_exit(data, 0);
}
