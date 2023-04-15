/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:10:28 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/15 21:01:47 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

/*
    Mimi
    Déplacement de toutes les fonctions d'affichage ici par soucis
    de propreté, de claireté et de norme
*/

void	afflist(t_list *list, char *name)
{
	(void)name;
	while (list)
	{
		printf("\e[1;33mToken : [%s]\n\e[0m", (char *)list->content);
		if (!list->next)
			break ;
		list = list->next;
	}
}

void	afftab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("entre\n");
		printf("tab[%d] = %s et la taille = %zu\n", \
			i, tab[i], ft_strlen(tab[i]));
		i++;
	}
}

void	afftoken(t_token *list, char *name)
{
	printf("-----------> %s <------------\n", name);
	(void)name;
	while (list)
	{
		printf("\e[0;31mToken : [%s]\e[0m", list->value);
		printf("\e[0;31mToken : [%d]\n\e[0m", list->t_type);
		list = list->next;
	}
}
