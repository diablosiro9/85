/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 11:01:52 by mla-rosa          #+#    #+#             */
/*   Updated: 2023/04/15 18:37:51 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list *));
	printf("content = %s\n", content);
	new->next = NULL;
	if (!new)
		return (NULL);
	if (content)
		new->content = content;
	else
		new->content = "";
	new->next = NULL;
	return (new);
}
