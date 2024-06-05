/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:41:02 by nfradet           #+#    #+#             */
/*   Updated: 2024/06/05 15:48:43 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtin(t_prompt *prompt)
{
	if (prompt->cmd == NULL)
		return (1);
	else if (ft_strncmp(prompt->cmd, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(prompt->cmd, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(prompt->cmd, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(prompt->cmd, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(prompt->cmd, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(prompt->cmd, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(prompt->cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

int ft_exe_builtin(t_data *data, char *cmd, t_string *args)
{
    if (cmd == NULL)
        return (1);
    if (ft_strncmp(cmd, "export", ft_maxlen(cmd, "export")) == 0)
        return (ft_export(data, args), 1);
    else if (ft_strncmp(cmd, "unset", ft_maxlen(cmd, "unset")) == 0)
        return (ft_unset(data, args), 1);
	else if (ft_strncmp(cmd, "env", ft_maxlen(cmd, "env")) == 0)
		return (aff_env(data->env, 1), 1);
    else if (ft_strncmp(cmd, "pwd", ft_maxlen(cmd, "pwd")) == 0)
        return (ft_printf("%s\n", data->pwd), 1);
    else if (ft_strncmp(cmd, "echo", ft_maxlen(cmd, "echo")) == 0)
        return (ft_echo(args), 1);
	else if (ft_strncmp(cmd, "cd", ft_maxlen(cmd, "cd")) == 0)
        return (ft_cd(data, args), 1);
	else if (ft_strncmp(cmd, "exit", ft_maxlen(cmd, "exit")) == 0)
        return (ft_exit(data, args), 1);
    return (0);
}
