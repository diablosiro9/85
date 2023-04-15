/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:26:59 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/05 19:56:04 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

int	closed_elem(char *str, char c)
{
	int		i;
	int		flag;
	int		counter;
	char	*start;

	i = 0;
	flag = 0;
	counter = 0;
	start = ft_strchr(str, c);
	if (start == NULL)
		return (1);
	while (start[i])
	{
		if (counter == 1 && start[i] == c)
		{
			counter = 0;
			flag = 0;
		}
		if (flag == 1 && start[i] == c)
		{
			counter = 1;
			flag = 0;
		}
		if (start[i] == c && counter != 1)
			flag = 1;
		i++;
	}
	return (counter);
}

int	delim_quote(char *tp, char c, char delim)
{
	int	i;
	int	flag;
	int	stock;

	i = 0;
	flag = 0;
	stock = 0;
	while (tp[i])
	{
		if (tp[i] == delim)
		{
			// printf("tp[i] == delim = %c\n", delim);
			if (flag == 1)
				flag = 0;
			flag = 1;
			stock = i;
		}
		if (tp[i] == c)
		{
			if (flag == 0)
				return (0);
		}
		i++;
	}
	return (1);
}

int	checking_closed(char *tp)
{
	int	val_test;

	if (!tp)
		return (-2);
	val_test = closed_elem(tp, '"');
	if (closed_elem(tp, '"') == 0 || closed_elem(tp, '\'') == 0)
	{
		if (closed_elem(tp, '"') == 0)
		{
			if (delim_quote(tp, '"', '\'') == 0)
				return (0);
		}
		else if (closed_elem(tp, '\'') == 0)
		{
			if (delim_quote(tp, '\'', '"') == 0)
				return (0);
		}		
	}
	val_test = closed_elem(tp, '\'');
	if (val_test == 0)
		return (-1);
	return (val_test);
}
