/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:13:44 by nfradet           #+#    #+#             */
/*   Updated: 2024/05/30 17:19:07 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	custom_exit(t_data *data, int status)
{
	if (data->is_exit == true)
	{
		write(STDERR_FILENO, "exit\n", 5);
		exit(status);
	}
	else
		last_signal = status;
	return (-1);
}