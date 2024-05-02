/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:34:55 by nfradet           #+#    #+#             */
/*   Updated: 2024/05/02 18:36:29 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_path(char *path, char *cmd)
{
	char	*join;
	char	*tmp;

	tmp = ft_strjoin("/", cmd);
	join = ft_strjoin(path, tmp);
	free(tmp);
	if (access(join, F_OK | R_OK) == 0)
		return (join);
	return (NULL);
}