/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:27:39 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/01 17:05:29 by nfradet          ###   ########.fr       */
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

// void	update_signal_env(t_data *data)
// {
// 	t_keyval	*kv;
// 	t_list		*node;

// 	kv = extract_var("?");
// 	kv->val = ft_itoa(last_signal);
// 	kv->is_exported = false;
// 	node = get_key(data, "?");
// 	if (node == NULL)
// 		add_var_to_env(data, kv);
// 	else
// 		modify_var(kv, node);
// }

char	*display_prompt(t_data	*data)
{
	char	*display;
	char	*line;
	char	*tmp;

	tmp = ft_strjoin(BOLD_GREEN"minishell:"BOLD_BLUE"~", data->pwd);
	display = ft_strjoin(tmp, NORMAL_WHITE"$ ");
	// update_signal_env(data);
	line = readline(display);
	free(tmp);
	free(display);
	if (line == NULL)
	{
		ft_printf("exit\n");
		ft_lstclear(&data->env, &ft_free_keyval);
		// ft_free_data(data);
		exit(EXIT_SUCCESS);
	}
	add_history(line);
	return (line);
}

int	main(int argc, char **argv, char **env)
{
	char				*line;
	t_prompt			*prompt;
	t_data				data;

	(void)argc;
	(void)argv;
	prompt = NULL;
	ft_initenv(&data, env);
	rl_clear_history();
	while (1)
	{
		signal(SIGINT, handle_sigint);
    	data.pwd = getcwd(NULL, 0);
		line = display_prompt(&data);
		parse(line, &prompt, &data);
		ft_init_nb_cmd(&data, prompt);
		if (data.nb_cmd >= 1)
			ft_handle_execution(&data, prompt);
		// chain_display(&prompt);
		free_chain(&prompt);
		free(data.pwd);
		dup2(data.inout_save[READ_END], STDIN_FILENO);
		dup2(data.inout_save[WRITE_END], STDOUT_FILENO);
		ft_printf("last_signal : %d\n", last_signal);
	}
	ft_free_data(&data);
	rl_clear_history();
	return (0);
}
