/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:29:48 by asangerm          #+#    #+#             */
/*   Updated: 2024/04/26 17:55:15 by marvin           ###   ########.fr       */
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
char		*ft_add_history(char *line, char *last_line);
int			ft_maxlen(char *s1, char *s2);
void		aff_env(t_list *env, int type);

/* Env directory */
t_keyval	*extract_var(char *var);
void		ft_initenv(t_data *data, char **env);
char		*ft_getenv(t_data *data, char *arg);
int			find_var(char *src, char *to_find);
t_list		*cpy_env(t_data *data);

/* Builtins directory */
void		ft_export(t_data *data, char **arg);
int			is_sorted(t_list *lst);
void		swap(t_list **list);
t_list		*sort_env(t_data *data);

void		del_node(t_list *head, t_list *node);
t_list		*get_key(t_data *data, char *key);


/* Free directory */
void		ft_free_keyval(void *kv);

#endif