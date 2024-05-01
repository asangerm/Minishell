/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:27:39 by asangerm          #+#    #+#             */
/*   Updated: 2024/04/30 15:37:41 by nfradet          ###   ########.fr       */
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
	t_data		data;

	(void)argc;
	(void)argv;
	(void)env;
	prompt = NULL;
	ft_initenv(&data, env);
	rl_clear_history();
	while (1)
	{
		line = readline("minishell:~home/minishell$ ");
		add_history(line);
		parse(line, &prompt);
		ft_exe_builtin(&data, prompt->cmd, prompt->args);
		// chain_display(&prompt);
		free_chain(&prompt);
	}
	ft_lstclear(&(data.env), &ft_free_keyval);
	return (0);
}
