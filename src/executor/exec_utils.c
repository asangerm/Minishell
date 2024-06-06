/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:13:44 by nfradet           #+#    #+#             */
/*   Updated: 2024/05/31 16:25:06 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	custom_exit(t_data *data, int status)
{
	if (data->is_exit == true)
	{
		ft_free_data(data);
		exit(status);
	}
	else
		last_signal = status;
	return (-1);
}