/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:27:39 by asangerm          #+#    #+#             */
/*   Updated: 2024/04/27 20:03:18 by nfradet          ###   ########.fr       */
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

void	aff_str(void *str)
{
	ft_printf("%s\n", (char *)str);
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
	// (void)argv;
	// (void)env;
	t_data	data;

	ft_initenv(&data, env);
	ft_unset(&data, &argv[1]);
	aff_env(data.env, 1);
	// rl_clear_history();
	// while (1)
	// {
	// 	line = readline("minishell$ ");
	// 	add_history(line);
	// 	free(line);
	// }
	return (0);
}