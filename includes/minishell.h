/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:29:48 by asangerm          #+#    #+#             */
/*   Updated: 2024/05/30 16:46:23 by asangerm         ###   ########.fr       */
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
# define READ_END 0
# define WRITE_END 1

typedef enum
{
	true = 1,
	false = 0
}	t_bool;

typedef struct s_string
{
	char			*str;
	t_bool			type;
	struct s_string	*next;
}	t_string;

typedef	struct s_keyval
{
	char	*key;
	char	*val;
	t_bool	is_exported;
}	t_keyval;

typedef struct s_prompt
{
	char			*line;
	char			*cmd;
	t_string		*args;
	t_string		*file_in;
	char			*delim;
	t_string		*file_out;
	t_list			*var;
	struct s_prompt	*next;
}	t_prompt;

typedef struct s_pipe
{
	int	fd[2];
}	t_pipe;

typedef struct s_data
{
	char	**paths;
	int		nb_cmd;
	t_pipe	*pipes;
	t_pipe	files_redir;
	t_list	*env;
	char	*pwd;
	int		inout_save[2];
}	t_data;

/* Parsing directory */
int			ft_maxlen(char *s1, char *s2);
void		aff_env(t_list *env, int type);

/* Env directory */
t_list		*cpy_env(t_data *data);
t_keyval	*extract_var(char *var);
t_keyval	*cpy_keyval(t_keyval *kv);
void		ft_initenv(t_data *data, char **env);
int			ft_strlen_until(char *str, char stop_char);
void		add_var_to_env(t_data *data, t_keyval *kv);
void		ft_handle_var_env(t_data *data, t_prompt *prompt);

/* Builtins directory */
void		swap(t_list **list);
char		*cut_plus(char *key);
int			is_sorted(t_list *lst);
void		ft_echo(t_string *args);
t_list		*sort_env(t_data *data);
int			ft_is_builtin(t_prompt *prompt);
t_list		*get_key(t_data *data, char *key);
char		*get_value(t_list *env, char *key);
void		ft_cd(t_data *data, t_string *args);
void		ft_unset(t_data *data, t_string *args);
void		ft_export(t_data *data, t_string *args);
int			builtins_err_handler(char *err_msg, char *variable);
int  	 	ft_exe_builtin(t_data *data, char *cmd, t_string *args);

/* Executor */
char		**ft_lst_to_tab(t_list *env);
void		ft_create_pipes(t_data *data);
char		**ft_cmd_to_tab(t_prompt *prompt);
void		ft_redirection_files(t_pipe files);
char		*check_path(char *path, char *cmd);
void		routine_pere(t_data *data, int nb_fork);
void		ft_redirection_pipes(t_data *data, int i);
int			ft_exe_cmd(t_data *data, t_prompt *prompt);
int			ft_executor(t_data *data, t_prompt *prompt);
t_pipe		ft_open_files(t_data *data, t_prompt *prompt);
void		ft_init_nb_cmd(t_data *data, t_prompt * prompt);
void		ft_exec_no_pipe(t_data *data, t_prompt *prompt);
void		ft_handle_execution(t_data *data, t_prompt *prompt);
void		close_pipes_excpt(t_pipe *pipes, int nb_pipes, int e1, int e2);

/* Free directory */
void		ft_free_tab(char **tab);
void		ft_free_keyval(void *kv);
void		var_display(t_list **var);
void		ft_free_data(t_data *data);

/* handlers_0.c */
void		cmd_handler(char *line, t_prompt *prompt, int *i);
void		var_handler(char *line, t_prompt *prompt, int *i);
void		args_handler(char *line, t_prompt *prompt, int *i, t_bool space);
void		file_in_handler(char *line, t_prompt *prompt, int *i);
void		file_out_handler(char *line, t_prompt *prompt, int *i);

/* parsing_0.c */
void		lexer(t_prompt **prompt);
char		*word_maker(char *line, int *i);
char		*double_quote(char *line, int *i);
char		*simple_quote(char *line, int *i);
void		parse(char *line, t_prompt **prompt,t_data *data);
void		big_if(char *line, t_prompt *prompt, int *i);

/* parsing_1.c */
char	*ft_strcat(char *str1, char *str2);
char	*gimme_str(char *line, int j, int i);
char	*semicolon_handler(char *line, t_data *data, int i, int j);
char	*word_env_check(char *line, int *i, t_data *data);

/* utils_chain_0.c */
t_prompt	*new_prompt(char *line);
void		free_chain(t_prompt **prompt);
void		free_content(t_prompt *chain);
t_prompt	*last_prompt(t_prompt **prompt);
void		prompt_add_back(t_prompt **prompt, t_prompt *new);

/* utils_chain_1.c */
int			test_equal(char *line, int *i);
void		chain_display(t_prompt **prompt);
char		**split_var(char *word, int i, int j);
void		tab_display(t_string **tab, char *type);
void		chain_creator(char *line, t_prompt **prompt);

/* utils_str_0.c */
t_string	*new_str(char *line, t_bool type);
void		free_str(t_string **str);
t_string	*last_str(t_string **str);
void		str_add_back(t_string **str, t_string *new);
int			lst_str_len(t_string *str);

#endif