/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:01:20 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/15 21:10:24 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

/*
    Mimi
    Déplacement de la fonction influencant sur une string dans le 
    dossier/.c dédié ./src/utils/list.c simplement par claireté et norme
*/

t_list	*ft_lstadd(t_list **alst, t_list *new)
{
	t_list	*tmp;

	tmp = *alst;
	printf("ADDDD\n");
	// printf("new = %s\n", (char *)new->content);
	if (tmp)
	{
		printf("la\n");
		printf("tmp->valueee = %s\n", tmp->content);
		if (tmp->next == NULL)
		{
			printf("toi\n");
			tmp->next = new;
		}
		else
		{
			while (tmp)
				tmp = tmp->next;
		}
		tmp->next = new;
	}
	else
	{
		printf("la2\n");
		// printf("tmp->valuexxee = %s\n", tmp->content);
		*alst = new;
		// (*alst)->next = NULL;
	}
	return (new);
}
