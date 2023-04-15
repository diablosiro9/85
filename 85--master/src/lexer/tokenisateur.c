/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisateur.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:40:16 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/15 17:13:09 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

t_token	*ft_token_new(int type, char *value)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->t_type = type;
	new->value = value;
	new->next = NULL;
	return (new);
}

t_token	*ft_token_add(t_token **alst, t_token *new)
{
	t_token	*tmp;

	tmp = *alst;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*alst = new;
	return (new);
}


t_token *delete_token(t_token* head, int position)
{
	int		i;
	t_token* new_head;
	t_token* current;
	t_token*	next_node;
	
	i = 0;
	new_head = NULL;
	current = NULL;
	next_node = NULL;
    if (head == NULL) {
        return head;
    }
    if (position == 0) {
		if (head->next)
        	new_head = head->next;
        free(head);
        return new_head;
    }
  	current = head;
    while (current != NULL && i < position - 1) {
        current = current->next;
		i++;
	}
    if (current == NULL || current->next == NULL) {
        return head;
    }
    next_node = current->next->next;
    free(current->next);
    current->next = next_node;
    return head;
}

void	ft_token_addf(t_token **alst, t_token *new)
{
	if (alst == NULL || new == NULL)
		return ;
	new->next = *alst;
	*alst = new;
}

/*
    Mimi
    Renommination de init_type à delete_token. Étant donné que toutes 
    les autres fonctions qui gère les tokens s'appelle ft_token_truc, autant
    formatter tous les noms des fonctions token de cette manière 
*/
void	ft_token_delete(t_token **l)
{
	t_token	*tmp;

	tmp = (*l);
	while ((*l) != NULL)
	{
		tmp = (*l);
		(*l) = (*l)->next;
		free(tmp);
	}
	free(*l);
}

/*
    Mimi
    Renommination de init_type à ft_token_init. Étant donné que toutes 
    les autres fonctions qui gère les tokens s'appelle ft_token_truc, autant
    formatter tous les noms des fonctions token de cette manière 
*/
void	ft_token_init(int type, char *value)
{
	if (ft_token_add(&g_data.token, ft_token_new(type, value)) == NULL)
		return ;
}


void	ft_list_delete(t_list **l)
{
	t_list	*tmp;

	tmp = (*l);
	while ((*l) != NULL)
	{
		tmp = (*l);
		(*l) = (*l)->next;
		free(tmp);
	}
	tmp = (*l);
	free(*l);
}


t_token	*tokenizateur(t_list *list, int delim)
{
	// printf("ICI\n");
	char	*tmp;
	int		i = 0;
	tmp = (char *)list->content;
	while (i < delim)
	{
		printf("la\n");
		tmp = (char *)list->content;
		if (tmp[0] == '|')
		{
			// printf("PIPE\n");
			ft_token_init(PIPE, list->content);
		}
		else if (tmp[0] == '$')
		{
			// printf("DOLLAR\n");
			ft_token_init(DOLLAR, list->content);
		}
		else if (tmp[0] == '>' && tmp[1] && tmp[1] == '>')
		{
			// printf("RREDIR\n");
			ft_token_init(RREDIR, list->content);
		}
		else if (tmp[0] == '>')
		{
			// printf("REDIR\n");
			if (ft_strlen(tmp) > 1)
				ft_token_init(REDIR, ft_strsub(tmp, 0, 1));
			else
				ft_token_init(REDIR, tmp);
		}
		else if (tmp[0] == '<' && tmp[1] && tmp[1] == '<')
		{
			// printf("HERE_DOC\n");
			ft_token_init(HERE_DOC, list->content);
		}
		else if (tmp[0] == '<')
		{
			// printf("RREDIR\n");
			ft_token_init(REDIR, ft_strsub(tmp, 0, 1));
		}
		else if (tmp[0] == '"')
		{
			// printf("QUOTE\n");
			ft_token_init(QUOTE, list->content);
		}
		else if (tmp[0] ==  '\'')
		{
			// printf("SQUOTE\n");
			ft_token_init(SQUOTE, list->content);
		}
		else if (tmp[0] == '-')
		{
			// printf("OPTION\n");
			ft_token_init(OPTION, list->content);
		}
		else
		{
			// printf("WORD\n");
			ft_token_init(WORD, list->content);
		}
		i++;
		if (i < delim)
			list = list->next;
		else
			return (NULL);
	}
	ft_list_delete(&list);
	return (NULL);
}
