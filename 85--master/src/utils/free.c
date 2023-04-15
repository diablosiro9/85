/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:55:53 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/04 13:56:06 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

/*
    Mimi
    Déplacement de la fonction influencant sur une string dans le 
    dossier/.c dédié ./src/utils/free.c simplement par claireté et norme
*/

void	free_tab(char **cmd)
{
	int	i;

	i = 0;
	if (cmd == NULL)
		return ;
	while (cmd[i])
		free(cmd[i++]);
	free(cmd);
}
