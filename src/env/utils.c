/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:15:54 by nfradet           #+#    #+#             */
/*   Updated: 2024/04/15 16:52:00 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_var(char *src, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	// if (to_find == NULL || src == NULL)
	while (src[i] && src[i] != '=')
	{
		if (to_find[j] && src[i] == to_find[j])
			j++;
		else
			return (1);
		i++;
	}
	if (to_find[j] == '\0' && i == j)
		return (0);
	else
		return (1);
}
