/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:27:39 by asangerm          #+#    #+#             */
/*   Updated: 2024/04/15 19:19:03 by nfradet          ###   ########.fr       */
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
	// char 	*line;
	// t_data	data;
	t_keyval	kv;

	extract_var(&kv, argv[1]);
	// ft_initenv(&data, env);
	// ft_lstiter(data.env, &aff_str);
	ft_printf("key : %s, val : %s\n", kv.key, kv.val);
	// ft_printf("%s\n", ft_getenv(&data, argv[1]));

	// rl_clear_history();
	// while (1)
	// {
	// 	line = readline("minishell$ ");
	// 	add_history(line);
	// 	free(line);
	// }
	return (0);
}