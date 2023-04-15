/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:19:11 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/15 18:28:42 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

int	token_size(void)
{
	t_data	ptr;
	int		i;

	i = 0;
	ptr = g_data;
	if (g_data.token)
	{
		while (g_data.token)
		{
			i++;
			g_data.token = g_data.token->next;
		}
	}
	g_data = ptr;
	return (i);
}

void	checking_solo_name(t_token *tmp)
{
	if (token_size() == 1)
	{
		if (tmp->t_type == 4 || tmp->t_type == 5 || tmp->t_type == 6
			|| tmp->t_type == 1 || tmp->t_type == 2)
		{
			if (ft_strlen(tmp->value) < 2)
			{
				if (tmp->t_type == 6)
					printf("Us_Bash: $: command not found\n");
				else if (tmp->t_type == 1 || tmp->t_type == 2)
					printf("Us_Bash2: syntax error near\
						unexpected token 'newline'\n");
				return ;
			}
		}
	}
}

void	*solo_command(void)
{
	t_token	*tmp;

	tmp = g_data.token;
	if (token_size() == 1 && tmp->t_type != 3)
	{
		checking_solo_name(tmp);
		g_data.token = tmp;
	}
	return ((void *)g_data.token->value);
}

void	*manage_double(void)
{
	t_token	*tmp;

	tmp = g_data.token;
	if (token_size() > 1)
	{
		while (tmp)
		{
			if (tmp->t_type == 0 && tmp->next == NULL)
            {
                printf("Us_Bash: syntax error near unexpected token '|'\n");
                return (NULL);
            }
            if (tmp->t_type == 0 && tmp->next->t_type == 0)
            {
                printf("Us_Bash: syntax error near unexpected token '|'\n");
                return (NULL);
            }

			tmp = tmp->next;
		}
	}
	return ((void *)g_data.token->value);
}

t_list	*token_to_list()
{
	t_list	*tmp = NULL;
	t_token	*stck = NULL;
	char	*stock;

	stock = NULL;
	// ft_list_delete(&str);
	stck = g_data.token;
	afftoken(g_data.token, "token_to_list");
	while (stck){
		printf("Stck->value = %s\n", stck->value);
		stock = stck->value;
		printf("Stck->value = %s\n", stck->value);
		ft_lstadd(&tmp, ft_lstnew(stock));
		// str->content = stck->value;
		// printf("tmp->value = %s\n", tmp->content);
		if (stck)
			stck = stck->next;
	}
	// free(str);
	// str = tmp;
	return (tmp);
}

t_list	*ft_parsor(t_list *str)
{
	t_list	*res;
	// char	*stock = str->content;
	
	res = NULL;
	(void)str;
	// s// afflist(str, "what\n");
	
	if (find_all_dollars() == NULL)
		return (NULL);
	if (solo_command() == NULL)
		return (NULL);
	else if (manage_double() == NULL)
		return (NULL);
	afftoken(g_data.token, "nu");

	split_cmd_file();

	afftoken(g_data.token, "nu");
	// printf("Stock - %s\n", stock);
	res = token_to_list();
	afftoken(g_data.token, "nu");

	// ft_list_delete(&str);
	// printf("str->= %s\n", str->content);
	// str = res;
	// char c;
	// read(0, &c, 1);
	return (res);
}
