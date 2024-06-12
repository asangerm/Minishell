/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:29:48 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/12 15:47:29 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/src/libft.h"
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
# include <termios.h>

# define EXPORT_ERR "minishell: export: `%s': not a valid identifier\n"
# define HD_ERR "minishell: warning: here-document (wanted `%s')\n"
# define SYNTH_ERROR "minishell: syntax error near unexpected token `%s'\n"
# define QUOTE_ERROR "minishell: error: unclosed quote\n"
# define CMD_NOT_FOUND "minishell: %s: command not found\n"
# define NO_SUCH_FILE "-minishell: %s: No such file or directory\n"
# define BOLD_GREEN "\033[1;32m"
# define BOLD_BLUE	"\033[1;34m"
# define NORMAL_WHITE	"\033[0m"
# define READ_END 0
# define WRITE_END 1

extern int	g_last_signal;

typedef enum s_bool
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

typedef struct s_keyval
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

typedef struct s_indexes
{
	int	i;
	int	j;
}	t_indexes;

typedef struct s_data
{
	t_prompt	*prompt;
	pid_t		ppid;
	char		**paths;
	int			nb_cmd;
	t_pipe		*pipes;
	t_pipe		files_redir;
	t_list		*env;
	char		*old_pwd;
	char		*pwd;
	int			inout_save[2];
	t_bool		is_exit;
	t_bool		is_in_exec;
}	t_data;

/* Parsing directory */
int			ft_maxlen(char *s1, char *s2);
void		handle_sigint_cmd(int signal);
void		aff_env(t_list *env, int type);

void		init_pwd(t_data *data);
void		handle_sigint(int signal);
void		handle_sigint_cmd(int signal);

/* Env directory */
t_list		*cpy_env(t_data *data);
char		*kv_to_str(t_keyval *kv);
t_keyval	*cpy_keyval(t_keyval *kv);
void		update_shlvl(t_data *data);
void		ft_initenv(t_data *data, char **env);
void		modify_var(t_keyval *kv, t_list *key);
void		ft_init_data(t_data *data, char **env);
int			ft_strlen_until(char *str, char stop_char);
void		add_var_to_env(t_data *data, t_keyval *kv);
t_keyval	*extract_var(char *var, t_bool is_exported);
int			ft_handle_var_env(t_data *data, t_prompt *prompt);

/* Builtins directory */
void		swap(t_list **list);
char		*cut_plus(char *key);
int			is_sorted(t_list *lst);
void		ft_echo(t_string *args);
t_list		*sort_env(t_data *data);
int			check_exp_args(t_keyval *kv);
int			ft_is_builtin(t_prompt *prompt);
t_list		*get_key(t_data *data, char *key);
char		*get_value(t_list *env, char *key);
void		ft_cd(t_data *data, t_string *args);
void		ft_exit(t_data *data, t_string *args);
void		ft_unset(t_data *data, t_string *args);
void		ft_export(t_data *data, t_string *args);
int			aff_err(char *err_msg, char *variable);
int			ft_exe_builtin(t_data *data, char *cmd, t_string *args);

/* Executor */
int			ft_executor(t_data *data);
char		**lst_to_tab(t_list *env);
void		ft_create_pipes(t_data *data);
char		**cmd_to_tab(t_prompt *prompt);
void		ft_handle_execution(t_data *data);
void		ft_redirection_files(t_pipe files);
char		*check_path(char *path, char *cmd);
int			custom_exit(t_data *data, int status);
int			ft_heredoc(t_data *data, char *limiter);
void		ft_redirection_pipes(t_data *data, int i);
int			ft_exe_cmd(t_data *data, t_prompt *prompt);
t_pipe		ft_open_files(t_data *data, t_prompt *prompt);
void		ft_init_nb_cmd(t_data *data, t_prompt *prompt);
void		ft_exec_no_pipe(t_data *data, t_prompt *prompt);
void		routine_pere(t_data *data, int nb_fork, pid_t last_pid);
void		close_pipes_excpt(t_pipe *pipes, int nb_pipes, int e1, int e2);

/* Free directory */
void		ft_free_tab(char **tab);
void		ft_free_keyval(void *kv);
void		var_display(t_list **var);
void		ft_free_data(t_data *data);

/* extracter_0.c */
char		*word_maker(char *line, int *i);
char		*double_quote(char *line, int *i);
char		*simple_quote(char *line, int *i);
char		*word_maker_env(char *line, int *i);

/* handlers_0.c */
char		*next_file(char *line, int *i);
void		var_handler(char *line, t_prompt *prompt, int *i);
void		args_handler(char *line, t_prompt *prompt, int *i);
int			file_in_handler(char *line, t_prompt *prompt, int *i);
int			file_out_handler(char *line, t_prompt *prompt, int *i);

/* parsing_0.c */
int			pipe_check(char *line);
int			quote_check(char *line);
int			lexer(t_prompt **prompt);
int			big_if(char *line, t_prompt *prompt, int *i);
int			parse(char *line, t_prompt **prompt, t_data *data);

/* parsing_1.c */
char		*ft_strcat(char *str1, char *str2);
char		*gimme_str(char *line, int j, int i);
char		*word_env_check(char *line, int *i, t_data *data);
char		*semicolon_handler(char *line, t_data *data, int i, int j);
char		*process_dollar(char *line, t_data *data,
				t_indexes *ind, char *new);

/* ft_newsplit.c */
void		skip_quote(char *str, int *i, char quote);
int			ft_newcount_words(char *str, char c);
char		*ft_newgimme(char *str, int i, int j);
char		*ft_newcheckwrd(int *j, char *str, char c);
char		**ft_newsplit(char const *s, char c);

/* utils_handler.c */
int			the_weeknd(char *line, int *i);
int			is_only_space(char *line, int i);
void		space_skipper(char *line, int *i);
void		delim_set(t_prompt *prompt, char *word);
void		cmd_handler(char *line, t_prompt *prompt, int *i);

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

/* utils_parsing.c */
int			error_checker(char *line);
char		*next_arg(char *line, int *i);
void		string_tab_display(char **args);
void		quote_skip(char *line, int	*i, int *valid);

#endif