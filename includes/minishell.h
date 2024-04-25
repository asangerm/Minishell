/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:29:48 by asangerm          #+#    #+#             */
/*   Updated: 2024/04/25 16:57:13 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/src/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

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

#endif