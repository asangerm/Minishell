/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 22:38:51 by nfradet           #+#    #+#             */
/*   Updated: 2024/04/05 23:33:40 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_maxlen(char *s1, char *s2)
{
	if (ft_strlen(s1) > ft_strlen(s2))
		return (ft_strlen(s1));
	else
		return (ft_strlen(s2));
}

static int	ft_is_added_to_history(char *line, char *last_line)
{
	if (ft_strncmp(line, "\0", 1) == 0 || line[0] == ' ')
		return (0);
	else if (last_line == NULL)
		return (1);
	else if (ft_strncmp(line, last_line, ft_maxlen(line, last_line)) != 0)
		return (1);
	return (0);
}

char	*ft_add_history(char *line, char *last_line)
{

	if (ft_is_added_to_history(line, last_line) == 1)
	{
		add_history(line);
		if (last_line != NULL)
			free(last_line);
		last_line = malloc(sizeof(char) * (ft_strlen(line) + 1));
		ft_strlcpy(last_line, line, ft_strlen(line) + 1);
	}
	return (last_line);
}
