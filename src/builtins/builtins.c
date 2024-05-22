/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:41:02 by nfradet           #+#    #+#             */
/*   Updated: 2024/05/22 14:40:51 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_exe_builtin(t_data *data, char *cmd, t_string *args)
{
    if (ft_strncmp(cmd, "export", ft_maxlen(cmd, "export")) == 0)
        return (ft_export(data, args));
    else if (ft_strncmp(cmd, "unset", ft_maxlen(cmd, "unset")) == 0)
        return (ft_unset(data, args), 1);
	else if (ft_strncmp(cmd, "env", ft_maxlen(cmd, "env")) == 0)
		return (aff_env(data->env, 1), 1);
    else if (ft_strncmp(cmd, "pwd", ft_maxlen(cmd, "pwd")) == 0)
        return (ft_printf("%s\n", data->pwd), 1);
    else if (ft_strncmp(cmd, "echo", ft_maxlen(cmd, "echo")) == 0)
        return (ft_echo(args), 1);
    return (0);
}
