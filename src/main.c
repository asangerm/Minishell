/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:27:39 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/12 17:19:37 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_signal;

void	handle_sigint_cmd(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		g_last_signal = 130;
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
		g_last_signal = 130;
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

void	parse_n_exec(t_data *data, char *line)
{
	g_last_signal = parse(line, &(data->prompt), data);
	if (g_last_signal == 0)
	{
		ft_init_nb_cmd(data, data->prompt);
		if (data->nb_cmd >= 1)
			ft_handle_execution(data);
	}
}


int	main(int argc, char **argv, char **env)
{
	char				*line;
	t_data				data;

	(void )argv;
	if (argc > 1)
		return (aff_err("minishell :Too many arguments\n", NULL), 1);
	ft_init_data(&data, env);
	rl_clear_history();
	while (1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		init_pwd(&data);
		line = display_prompt(&data);
		parse_n_exec(&data, line);
		free_chain(&(data.prompt));
		dup2(data.inout_save[READ_END], STDIN_FILENO);
		dup2(data.inout_save[WRITE_END], STDOUT_FILENO);
	}
	ft_free_data(&data);
	rl_clear_history();
	return (0);
}
