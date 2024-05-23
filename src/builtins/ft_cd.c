/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:51:20 by nfradet           #+#    #+#             */
/*   Updated: 2024/05/23 17:09:33 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_data *data, t_string *args)
{
	char	*val;

	val = get_value(data->env, "HOME");
	if (args == NULL)
	{
		if (val == NULL)
			ft_printf("minishell: cd: HOME not set\n");
		else
		{
			if (chdir(val) != 0)
				ft_printf("minishell: cd: %s: No such file or directory\n", val);
		}
	}
	else if (lst_str_len(args) > 1)
		ft_printf("minishell: cd: too many arguments");
	else if (chdir(args->str) != 0)
		ft_printf("minishell: cd: %s: No such file or directory\n", args->str);
}
