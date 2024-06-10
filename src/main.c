/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:27:39 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/10 17:25:32 by asangerm         ###   ########.fr       */
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

char	*display_prompt(t_data	*data)
{
	char	*display;
	char	*line;
	char	*tmp;

	tmp = ft_strjoin(BOLD_GREEN"minishell:"BOLD_BLUE"~", data->pwd);
	display = ft_strjoin(tmp, NORMAL_WHITE"$ ");
	line = readline(display);
	free(tmp);
	free(display);
	if (line == NULL)
	{
		ft_printf("exit\n");
		ft_free_data(data);
		exit(EXIT_SUCCESS);
	}
	add_history(line);
	return (line);
}

int	main(int argc, char **argv, char **env)
{
	char				*line;
	t_data				data;

	(void)argc;
	(void)argv;
	ft_initenv(&data, env);
	rl_clear_history();
	while (1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
    	data.pwd = getcwd(NULL, 0);
		line = display_prompt(&data);
		last_signal = parse(line, &data.prompt, &data);
		if (last_signal == 0)
		{
			ft_init_nb_cmd(&data, data.prompt);
			if (data.nb_cmd >= 1)
				ft_handle_execution(&data);
			//chain_display(&(data.prompt));
		}
		free_chain(&(data.prompt));
		free(data.pwd);
		dup2(data.inout_save[READ_END], STDIN_FILENO);
		dup2(data.inout_save[WRITE_END], STDOUT_FILENO);
		// ft_printf("last_signal : %d\n", last_signal);
	}
	ft_free_data(&data);
	rl_clear_history();
	return (0);
}
