/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:29:48 by asangerm          #+#    #+#             */
/*   Updated: 2024/04/19 16:59:25 by asangerm         ###   ########.fr       */
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
	char			*line;
	char			*cmd;
	char			**args;
	char			*file_in;
	char			*file_out;
	struct s_prompt	*next;
}	t_prompt;

/* parsing.c */

char		*file_finder(int i, char *line);
void		parse(char *line, t_prompt **prompt);
void		redirection_handler(t_prompt **prompt);
char		*word_maker(char *line, int i, int j, int l);

/* utils_chain_0.c */

t_prompt	*new_prompt(char *line);
void		free_chain(t_prompt **prompt);
void		free_content(t_prompt *chain);
t_prompt	*last_prompt(t_prompt **prompt);
void		prompt_add_back(t_prompt **prompt, t_prompt *new);

/* utils_chain_1.c */

void		chain_display(t_prompt **prompt);
void		chain_creator(char *line, t_prompt **prompt);

#endif