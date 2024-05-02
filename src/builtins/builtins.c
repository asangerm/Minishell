/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:41:02 by nfradet           #+#    #+#             */
/*   Updated: 2024/05/01 15:35:48 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_exe_builtin(t_data *data, char *cmd, t_string *args)
{
    if (ft_strncmp(cmd, "export", ft_maxlen(cmd, "export")) == 0)
        ft_export(data, args);
    else if (ft_strncmp(cmd, "unset", ft_maxlen(cmd, "unset")) == 0)
        ft_unset(data, args);    
	else if (ft_strncmp(cmd, "env", ft_maxlen(cmd, "env")) == 0)
		aff_env(data->env, 1);
    else if (ft_strncmp(cmd, "pwd", ft_maxlen(cmd, "pwd")) == 0)
        ft_printf("%s\n", data->pwd);
}
