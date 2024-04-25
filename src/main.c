/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:27:39 by asangerm          #+#    #+#             */
/*   Updated: 2024/04/25 14:04:12 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(char **prompt)
{
	int	i;

	i = 0;
	while (prompt[i])
	{
		ft_printf("arg %d = %s\n", i, prompt[i]);
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_prompt	*prompt;

	(void)argc;
	(void)argv;
	(void)env;
	prompt = NULL;
	while (1)
	{
		line = readline("minishell:~home/minishell$ ");
		parse(line, &prompt);
		chain_display(&prompt);
		free_chain(&prompt);
	}
	return (0);
}
