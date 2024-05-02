/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:27:39 by asangerm          #+#    #+#             */
/*   Updated: 2024/05/02 15:17:09 by nfradet          ###   ########.fr       */
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
	t_pipe		files;
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
		// files = ft_open_files(prompt);
		ft_printf("%d | %d\n", files.fd[0], files.fd[1]);
		ft_exe_builtin(&data, prompt->cmd, prompt->args);
		chain_display(&prompt);
		free_chain(&prompt);
	}
	ft_lstclear(&(data.env), &ft_free_keyval);
	return (0);
}
