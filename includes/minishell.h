/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:29:48 by asangerm          #+#    #+#             */
/*   Updated: 2024/05/10 16:52:13 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/src/libft.h"
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <unistd.h>

# define EXPORT_ERR "minishell: syntax error near unexpected token `%s'\n"
# define BOLD_GREEN "\033[1;32m"
# define BOLD_BLUE	"\033[1;34m"
# define NORMAL_WHITE	"\033[0m"

typedef struct s_string
{
	char			*str;
	struct s_string	*next;
}	t_string;

typedef struct s_prompt
{
	char			*line;
	char			*cmd;
	t_string		*args;
	t_string		*file_in;
	t_string		*file_out;
	struct s_prompt	*next;
}	t_prompt;

typedef	struct s_keyval
{
	char	*key;
	char	*val;
}	t_keyval;

typedef struct s_pipe
{
	int	fd[2];
}	t_pipe;

typedef struct s_data
{
	char	**paths;
	int		nb_cmd;
	t_pipe	*pipes;
	t_list	*env;
	char	*pwd;
	// t_list	*variables;
}	t_data;

/* Parsing directory */
int			ft_maxlen(char *s1, char *s2);
void		aff_env(t_list *env, int type);

/* Env directory */
t_keyval	*extract_var(char *var);
void		ft_initenv(t_data *data, char **env);
t_list		*cpy_env(t_data *data);
int			ft_strlen_until(char *str, char stop_char);

/* Builtins directory */
int  	 	ft_exe_builtin(t_data *data, char *cmd, t_string *args);
int			builtins_err_handler(char *err_msg, char *variable);
int			ft_export(t_data *data, t_string *args);
void		ft_unset(t_data *data, t_string *args);
t_list		*get_key(t_data *data, char *key);
t_list		*sort_env(t_data *data);
int			is_sorted(t_list *lst);
void		swap(t_list **list);

/* Pipes */
t_pipe		ft_open_files(t_prompt *prompt);
char		*check_path(char *path, char *cmd);
char		**ft_cmd_to_tab(t_prompt *prompt);
char		**ft_lst_to_tab(t_list *env);
void		ft_redirection_files(t_pipe files);
int			ft_handle_pipes(t_data *data, t_prompt *prompt);
void		routine_pere(t_pipe *pipes, int nb);
void		close_pipes_excpt(t_pipe *pipes, int nb_pipes, int e1, int e2);
void		ft_init_nb_cmd(t_data *data, t_prompt * prompt);
int			ft_exe_cmd(t_data *data, t_prompt *prompt);
void		ft_exec_no_pipe(t_data *data, t_prompt *prompt);

/* Free directory */
void		ft_free_keyval(void *kv);

/* handlers_0.c */
void		cmd_handler(char *line, t_prompt *prompt, int *i);
void		args_handler(char *line, t_prompt *prompt, int *i);
void		file_out_handler(char *line, t_prompt *prompt, int *i);
void		file_in_handler(char *line, t_prompt *prompt, int *i);

/* parsing_0.c */
void		lexer(t_prompt **prompt);
char		*word_maker(char *line, int *i);
char		*double_quote(char *line, int *i);
void		parse(char *line, t_prompt **prompt);
void		big_if(char *line, t_prompt *prompt, int *i);

/* utils_chain_0.c */
t_prompt	*new_prompt(char *line);
void		free_chain(t_prompt **prompt);
void		free_content(t_prompt *chain);
t_prompt	*last_prompt(t_prompt **prompt);
void		prompt_add_back(t_prompt **prompt, t_prompt *new);

/* utils_chain_1.c */
void		chain_display(t_prompt **prompt);
void		tab_display(t_string **tab, char *type);
void		chain_creator(char *line, t_prompt **prompt);

/* utils_str_0.c */
t_string	*new_str(char *line);
void		free_str(t_string **str);
t_string	*last_str(t_string **str);
void		str_add_back(t_string **str, t_string *new);
int			lst_str_len(t_string *str);

#endif