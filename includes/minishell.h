/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:29:48 by asangerm          #+#    #+#             */
/*   Updated: 2024/04/15 19:19:36 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/src/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_prompt
{
	char	*cmd;
	char	*args;
}	t_prompt;

typedef	struct s_keyval
{
	char	*key;
	char	*val;
}	t_keyval;

typedef struct s_data
{
	char	**paths;
	t_list	*env;
	t_list	*variables;
}	t_data;

/* Parsing directory */
char	*ft_add_history(char *line, char *last_line);
int		ft_maxlen(char *s1, char *s2);
int		parse_env(t_data *data);
void	aff_env(char **env);
void	parse(char *line);

/* Env directory */
void	extract_var(t_keyval *keyval, char *var);
void	ft_initenv(t_data *data, char **env);
char	*ft_getenv(t_data *data, char *arg);
int		find_var(char *src, char *to_find);

#endif