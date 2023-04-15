/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 18:55:48 by imac21            #+#    #+#             */
/*   Updated: 2023/04/15 00:43:06 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

void	ft_pwd(int redir)
{
	char	pwd[1000];
	char	*tmp = NULL;
	
	tmp = getcwd(pwd, sizeof(pwd));
	if (tmp == NULL)
		return ;
	ft_putstr_fd(tmp, redir);
	ft_putchar_fd('\n', redir);
	return ;
}

t_env *delete_node(t_env* head, int position) {
    if (head == NULL) {
        // la liste est vide
        return head;
    }
    // supprime le premier élément
    if (position == 0) {
       	t_env* new_head = head->next;
        free(head);
        return new_head;
    }
    // supprime un élément dans la liste
    t_env* current = head;
    for (int i = 0; current != NULL && i < position - 1; i++) {
        current = current->next;
    }
    if (current == NULL || current->next == NULL) {
        // la position est en dehors de la liste
        return head;
    }
    t_env* next_node = current->next->next;
    free(current->next);
    current->next = next_node;
    return head;
}

void	ft_unset(char *name)
{
	char	*path = NULL;
	t_env	*tmp = g_data.env;
	int		i = 0;

	if (!name)
		return ;
	// printf("la \n");
	// printf("name == %s\n", name);
	if (name == NULL || name[0] == '$')
	{
		if (name[0] == '$')
		{
			ft_putstr_fd("unset: ", STDERR_FILENO);
			ft_putstr_fd(path, STDERR_FILENO);
			ft_putchar_fd(':', STDERR_FILENO);
			ft_putstr_fd(" not a valid identifier\n", STDERR_FILENO);
			return ;
		}
		else
			return ;
	}
	// printf("name == %s\n", name);

	// printf("la\n");
	path = search_env_content_do(g_data.env, name);
	// printf("path = %s\n", path);
	if (path == NULL && name == NULL)
		return ;
	if (path != NULL)
	{
		while (strcmp(tmp->name, name) != 0 && tmp)
		{
			tmp = tmp->next;
			i++;
		}
		if (strcmp(tmp->name, name) == 0)
			delete_node(g_data.env, i);
	}
}
