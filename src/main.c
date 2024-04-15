/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:27:39 by asangerm          #+#    #+#             */
/*   Updated: 2024/04/15 17:03:05 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(char **prompt)
{
	int	i;

	i = 0;
	while(prompt[i])
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
	(void)argc;
	(void)argv;
	(void)env;
	char 	*line;
	char 	*last_line;
	t_data	data;

	ft_initenv(&data, env);
	// ft_lstiter(data.env, &aff_str);
	// ft_printf("%s\n", find_var(argv[2], argv[1]));
	// ft_printf("%s\n", ft_getenv(&data, argv[1]));

	parse_env(&data);
	rl_clear_history();
	last_line = NULL;
	while (1)
	{
		line = readline("minishell$ ");
		parse(line);
		//prompt = ft_split(line, ' ');
		//print_prompt(prompt);
		last_line = ft_add_history(line, last_line);
		free(line);
	}
	return (0);
}