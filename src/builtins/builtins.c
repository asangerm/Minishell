/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:41:02 by nfradet           #+#    #+#             */
/*   Updated: 2024/05/17 20:32:22 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_exe_builtin(t_data *data, char *cmd, t_string *args)
{
    if (cmd == NULL)
        return (1);
    if (ft_strncmp(cmd, "export", ft_maxlen(cmd, "export")) == 0)
        return (ft_export(data, args));
    else if (ft_strncmp(cmd, "unset", ft_maxlen(cmd, "unset")) == 0)
        return (ft_unset(data, args), 1);
	else if (ft_strncmp(cmd, "env", ft_maxlen(cmd, "env")) == 0)
		return (aff_env(data->env, 1), 1);
    else if (ft_strncmp(cmd, "pwd", ft_maxlen(cmd, "pwd")) == 0)
        return (ft_printf("%s\n", data->pwd), 1);
    return (0);
}
