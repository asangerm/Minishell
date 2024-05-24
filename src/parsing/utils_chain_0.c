/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_chain_0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:10:09 by asangerm          #+#    #+#             */
/*   Updated: 2024/05/24 18:42:57 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Cette fonction crée et initialise un node de type prompt
*/
t_prompt	*new_prompt(char *line)
{
	t_prompt	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->line = line;
	new->cmd = NULL;
	new->args = NULL;
	new->file_in = NULL;
	new->file_out = NULL;
	new->delim = NULL;
	new->next = NULL;
	new->var = NULL;
	return (new);
}

/*
	Un équivalent de lst_last mais adapté à notre structure
*/
t_prompt	*last_prompt(t_prompt **prompt)
{
	t_prompt	*new;

	new = *prompt;
	if (!new)
		return (NULL);
	while (new->next)
		new = new->next;
	return (new);
}

/*
	Fonction qui libère la mémoire du contenu des structures
*/
void	free_content(t_prompt *chain)
{
	if (chain->cmd)
		free(chain->cmd);
	if (chain->file_in)
		free_str(&(chain->file_in));
	if (chain->file_out)
		free_str(&(chain->file_out));
	if (chain->line)
		free(chain->line);
	if (chain->args)
		free_str(&(chain->args));
	if (chain->var)
		ft_lstclear(&(chain->var), &ft_free_keyval);
}

/*
	Fonction qui libère le node, cours, cours petit node
*/
void	free_chain(t_prompt **prompt)
{
	t_prompt	*current;
	t_prompt	*next;

	current = *prompt;
	while (current)
	{
		next = current->next;
		free_content(current);
		free(current);
		current = next;
	}
	*prompt = NULL;
}

/*
	En gros c'est lst_add_back mais voilà
*/
void	prompt_add_back(t_prompt **prompt, t_prompt *new)
{
	t_prompt	*tmp;

	if (!*prompt)
	{
		*prompt = new;
		return ;
	}
	tmp = last_prompt(prompt);
	tmp->next = new;
}
