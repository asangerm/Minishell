/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:27:39 by asangerm          #+#    #+#             */
/*   Updated: 2024/05/06 11:51:14 by nfradet          ###   ########.fr       */
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
	char		*display;
	char		*tmp;
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
		tmp = ft_strjoin("minishell:~", data.pwd);
		display = ft_strjoin(tmp, "$ ");
		// ft_printf("minishell:~%s$ ", data.pwd);
		line = readline(display);
		add_history(line);
		parse(line, &prompt);
		ft_init_nb_cmd(&data, prompt);
		if (data.nb_cmd == 1)
			ft_exec_no_pipe(&data, prompt);
		else if (ft_handle_pipes(&data, prompt) == 0)
			return (0);
		// chain_display(&prompt);
		free(tmp);
		free(display);
		free_chain(&prompt);
	}
	ft_lstclear(&(data.env), &ft_free_keyval);
	return (0);
}
