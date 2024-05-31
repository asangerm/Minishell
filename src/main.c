/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:27:39 by asangerm          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2024/05/30 17:18:31 by nfradet          ###   ########.fr       */
=======
/*   Updated: 2024/05/31 14:03:04 by nfradet          ###   ########.fr       */
>>>>>>> Stashed changes
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
	while (1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
    	data.pwd = getcwd(NULL, 0);
		tmp = ft_strjoin(BOLD_GREEN"minishell:"BOLD_BLUE"~", data.pwd);
		display = ft_strjoin(tmp, NORMAL_WHITE"$ ");
		line = readline(display);
		// data.is_exit = 123124134;
		// printf("is_exit = %d\n", data.is_exit);
		free(tmp);
		free(display);
		add_history(line);
		parse(line, &prompt, &data);
		ft_init_nb_cmd(&data, prompt);
		if (data.nb_cmd >= 1)
		{
			signal(SIGINT, handle_sigint_cmd);
			ft_handle_execution(&data, prompt);
<<<<<<< Updated upstream
		}
		// chain_display(&prompt);
=======
		chain_display(&prompt);
>>>>>>> Stashed changes
		free_chain(&prompt);
		free(data.pwd);
		// free(line);
		dup2(data.inout_save[READ_END], STDIN_FILENO);
		dup2(data.inout_save[WRITE_END], STDOUT_FILENO);
		ft_printf("last_signal : %d\n", last_signal);
		ft_printf("exit_status : %d\n", data.exit_status);
	}
	ft_free_data(&data);
	rl_clear_history();
	return (0);
}
