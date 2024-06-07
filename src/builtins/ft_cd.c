/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:51:20 by nfradet           #+#    #+#             */
/*   Updated: 2024/06/07 15:53:46 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_cd_args(t_data *data, t_string *args)
{
	if (lst_str_len(args) > 1)
	{
		aff_err("minishell: cd: too many arguments\n", NULL);
		custom_exit(data, 1);
	}
	else if (chdir(args->str) != 0)
	{
		aff_err(NO_SUCH_FILE, ft_strdup(args->str));
		custom_exit(data, 1);
	}
}

void	ft_cd(t_data *data, t_string *args)
{
	char	*val;

	val = get_value(data->env, "HOME");
	if (args == NULL)
	{
		if (val == NULL)
		{
			aff_err("minishell: cd: HOME not set\n", NULL);
			custom_exit(data, 1);
		}
		else if (chdir(val) != 0)
		{
			aff_err(NO_SUCH_FILE, ft_strdup(val));
			custom_exit(data, 1);
		}
	}
	else
		check_cd_args(data, args);
}
