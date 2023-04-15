/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:20:25 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/12 15:24:30 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"
#include <readline/readline.h>
#include <readline/history.h>

int	det_nb_hd()
{
	t_token *tmp;
	int	flag = 0;

	tmp = g_data.token;
	while (tmp)
	{
		if (tmp->t_type == 9 && tmp->next->t_type == 10)
			flag++;
		tmp = tmp->next;
	}
	if (flag > 1)
		return (2);
	return flag;
}

int	det_hd()
{
	t_token	*tmp;

	tmp = g_data.token;
	while (tmp)
	{
		if (tmp->t_type == 9 && (!tmp->next || tmp->next->t_type != 10))
		{
			if (!tmp->next)
			{
				printf("bash: syntax error near unexpected token `newline'\n");
				return (-1);
			}
			if (tmp->next->t_type == 0)
				printf("bash: syntax error near unexpected token `|'\n");
			if (tmp->next->t_type == 1)
				printf("bash: syntax error near unexpected token `<'\n");
			if (tmp->next->t_type == 2)
				printf("bash: syntax error near unexpected token `>'\n");
			if (tmp->next->t_type == 9)
				printf("bash: syntax error near unexpected token `<<'\n");
			return (-1);
		}
		if (tmp->t_type == 9 && tmp->next->t_type == 10)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

t_list	*simple_hd()
{
	//simple_hd, have to parse the token until the end_of_file, set it as delim for here_doc_fct
	t_token	*temp = g_data.token;
	int	i = 1;
	t_list	*stock = NULL;

	while (temp)
	{
		stock = ft_lstnew(temp->value);
		if (temp->t_type == 10)
			stock = here_doc(temp->value, i);
		temp = temp->next;
	}
	if (stock)
		return (stock);
	return (NULL);
}

char	**fill_hd_arg(char *path, char *name)
{
	char	**res = NULL;
	t_token	*tmp = NULL;
	int		i = 0;
	int		flag = 0;

	tmp = g_data.token;
	(void)path;
	while (tmp && (tmp->t_type == 8 || tmp->t_type == 7))
	{
		if (tmp->t_type == 7)
			flag = 1;
		i++;
		tmp = tmp->next;
	}
	res = malloc(sizeof(char *) * ((i * 2) + 1));
	if (!res || res == NULL)
		return (NULL);
	res[0] = ft_strdup(name);
	res[1] = ft_strdup("-");
	res[2] = NULL;
	return (res);
}

t_list	*here_doc(char *delim, int flag)
{
	char	*stock = NULL;
	t_list	*cmd = NULL;
	t_list	*tmp;
	// cmd = ft_lstnew((void *)delim);
	while (42)
	{
	 	// ft_putstr(">");
        // stock = get_next_line(0);
		stock = readline(">");
		
		tmp = ft_lstnew(stock);
		stock = tmp->content;
		if (strcmp(stock, delim) == 0)
			return (cmd);
		ft_lstadd(&cmd, tmp);
		if (flag == -1)
		{
			if (strcmp(stock, delim) == 0)
				return (cmd);
		}
		if (flag == 0)
		{
			if (ft_strchr(stock, '"'))
				return (cmd);
		}
		// printf("history->content = %s\n", history->content);
	}
	return (tmp);
}
