/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:15:54 by nfradet           #+#    #+#             */
/*   Updated: 2024/04/26 16:49:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * * aff_env
 * @param env l'environnement a afficher
 * @param type un entier (1 ou 2), qui indique l'affichage souhaite
 * Affiche l'environnement en parametre, 
 * Si type == 1, il est affiche selon la commande 'env'
 * Si type == 2, il est affiche selon la commande 'export'
 * @return void
*/
void	aff_env(t_list *env, int type)
{
	t_list		*lst;
	t_keyval	*kv;

	lst = env;
	while (lst)
	{
		kv = (t_keyval*)lst->content;
		if (type == 1)
		{
			if (kv->val != NULL)
				ft_printf("%s=%s\n", kv->key, kv->val);
		}
		else if (type == 2)
		{
			if (kv->val != NULL && kv->val[0] ==  '\0')
				ft_printf("declare -x %s=\"\"\n", kv->key);
			else if (kv->val == NULL)
				ft_printf("declare -x %s\n", kv->key);
			else if (kv->key[0] != '_')
				ft_printf("declare -x %s=\"%s\"\n", kv->key, kv->val);
		}
		lst = lst->next;
	}
}

/**
 * ft_maxlen
 * @param s1 une chaine de charactere
 * @param s2 une chaine de charactere
 * @return int la longueur de la plus grande chaine
*/
int	ft_maxlen(char *s1, char *s2)
{
	if (ft_strlen(s1) > ft_strlen(s2))
		return (ft_strlen(s1));
	return (ft_strlen(s2));
}

/**
 * cpy_keyval
 * @param kv pointeur sur structure t_keyval (duo key:value)
 * @return t_keyval* la copie de la structure passee en parametre
*/
t_keyval	*cpy_keyval(t_keyval *kv)
{
	t_keyval	*cpy;

	cpy = malloc(sizeof(t_keyval));
	cpy->key = NULL;
	cpy->key = NULL;
	cpy->key = ft_strdup(kv->key);
	cpy->val = ft_strdup(kv->val);
	return (cpy);
}

/**
 * cpy_env
 * @param data la structure data qui contient l'environnement utilise
 * @return t_list* une copie de l'environnement actuel
*/
t_list	*cpy_env(t_data *data)
{
	t_list		*cpy;
	t_list		*new;
	t_keyval	*kv_tmp;
	t_list		*i;

	i = data->env;
	cpy = NULL;
	while (i)
	{
		kv_tmp = cpy_keyval((t_keyval *)i->content);
		new = ft_lstnew((void *)kv_tmp);
		ft_lstadd_back(&cpy, new);
		i = i->next;
	}
	return (cpy);
}
