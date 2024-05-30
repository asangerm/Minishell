/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:27:39 by asangerm          #+#    #+#             */
/*   Updated: 2024/05/29 20:02:39 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	last_signal;

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

void	handle_sigint_cmd(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		last_signal = 130;
	}
}

void	handle_sigint(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		last_signal = 130;
	}
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
	// (void)env;
	prompt = NULL;
	ft_initenv(&data, env);
	rl_clear_history();
	last_signal = 0;
	while (1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
    	data.pwd = getcwd(NULL, 0);
		tmp = ft_strjoin(BOLD_GREEN"minishell:"BOLD_BLUE"~", data.pwd);
		display = ft_strjoin(tmp, NORMAL_WHITE"$ ");
		line = readline(display);
		free(tmp);
		free(display);
		add_history(line);
		parse(line, &prompt, &data);
		ft_init_nb_cmd(&data, prompt);
		if (data.nb_cmd >= 1)
		{
			signal(SIGINT, handle_sigint_cmd);
			ft_handle_execution(&data, prompt);
		}
		// chain_display(&prompt);
		free_chain(&prompt);
		free(data.pwd);
		// free(line);
		dup2(data.inout_save[READ_END], STDIN_FILENO);
		dup2(data.inout_save[WRITE_END], STDOUT_FILENO);
		ft_printf("%d\n", last_signal);
	}
	ft_free_data(&data);
	rl_clear_history();
	return (0);
}
