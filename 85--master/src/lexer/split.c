/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:49:18 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/15 20:40:14 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

// Mimi - La fonction est trop trop longue, 
//faut fractionner en plusieurs fonctions
void	tiray_case(int tmp, int i, int j, char **tab, char *str)
{
	tmp = i;
	while (str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
		i++;
	if (str[i] == ' ')
		i -= 1;
	tab[j] = ft_strsub(str, tmp, i);
	str = str + i;
	i = 0;
	j++;
}

void	dollar_case(int i, int j, int tmp, char *str, char **tab)
{
	tmp = i;
	while (str[i] != ' ' && str[i] != '\0')
		i++;
	tab[j] = ft_strsub(str, tmp, i);
	str = str + i;
	i = 0;
	j++;
}

char	**double_quote_case(int i, int j, int tmp, int flag, char *str, char **tab)
{
	tmp = i;
	i = i + 1;
	while (str[i] != '"')
	{
		i++;
		if (str[i] == '\0')
		{
			tab[j] = NULL;
			return (tab);
		}
	}
	tab[j] = ft_strsub(str, tmp, i + 1);
	tmp = 0;
	flag = 1;
	str = str + i + 1;
	i = 0;
	j++;
	return (NULL);
}

char	**simple_quote_case(int i, int j, int tmp, int flag, char *str, char **tab)
{
	tmp = i;
	i = i + 1;
	if (str[tmp] == '\'')
	{

		while (str[i] != '\'')
		{
			if (str[i] == '\0')
			{
				tab[j] = 0;
				return (tab);
			}
			i++;
		}
		if (i != 1)
			tab[j] = ft_strsub(str, tmp, i + 1);
		else
			tab[j] = ft_strsub(str, tmp + 1, i);
		str = str + i;
		i = 0;
		tmp = 0;
		flag = 1;
		j++;
	}
	else
	{

		while (str[i] != '\'')
		{
			if (str[i] == '\0')
			{
				tab[j] = NULL;
				return (tab);
			}
			i++;
		}
		if (str[i] == '\'')
		{
			if (str[i - 1] == '\'')
				tab[j] = ft_strsub(str, tmp + 1, i - 2);
			else
			{
				if (ft_isalpha(str[i - 1]) == 1)
					tab[j] = ft_strsub(str, tmp + 1, i - 1);
				else
				{
					if (ft_isalpha(str[i - 2]) == 1)
						tab[j] = ft_strsub(str, tmp + 1, i - 1);
					else
						tab[j] = ft_strsub(str, tmp + 1, i - 2);
				}
			}
		}
		else
			tab[j] = ft_strsub(str, tmp + 1, i);
		tmp = 0;
		flag = 1;
		str = str + i + 1;
		i = 0;
		j++;
	}
	return (NULL);
}

char	**others_case(int *i, int *j, int *tmp, int *flag, char *str, char **tab)
{
	tmp = i;
	printf("El laaasto\n");
	printf("Str = %s\n", str);
	printf("str + i = %s\n", str + *i);
	printf("i = %d\n", *i);
	if (str[*i] < 0 || str[*i] > 127)
	{
		tab[*j] = 0;
		return (tab);
	}
	while (str[*i] == ' ' && str[*i] == '\t')
		*i = *i + 1;
	if (str[*i] == '\'')
		*flag = 1;
	else if (str[*i] != ' ')
	{
		while (str[*i] != ' ' && str[*i] != '\t' && str[*i] != '\0')
			i++;
		if ((str[*i] == ' ' || str[*i] == '\t') && str[*i + 1])
		{
			tab[*j] = ft_strsub(str, *tmp, *i);
			i = i + 1;
		}
		else
		{
			if (tmp != i)
			{
				tab[*j] = ft_strsub(str, *tmp, *i);	
			}
			else
			{
				tab[*j] = NULL;
				printf("pr\n");

				return (tab);
			}
		}
		if (str + *i)
			str = str + *i;
		else
		{
			printf("peur\n");
			tab[*j + 1] = NULL;
			return (tab);
		}
		*i = 0;
		tmp = 0;
		j++;
	}
	return (NULL);
}

char	**ft_split(char *str)
{
	int		i;
	int		j;
	int		flag;
	int		tmp;
	char	**tab;

	i = 0;
	j = 0;
	tmp = 0;
	flag = 0;
	printf("stre = %s\n", str);
	tab = (char **)malloc(sizeof(char *) * (ft_strlen(str) + 1));
	while (str && str[i])
	{
		flag = 0;
		printf("repasse\n");
		if (str[i] == ' ')
		{
			while (str[i] == ' ' && str[i])
				i++;
			if (str[i] == '\0')
				return (NULL);
			str = str + i;
			i = 0;
		}
		if (!(str + i))
			return (tab);
		if (str[i] < 0 && str[i] > 127)
		{
			tab[j] = 0;
			return (tab);
		}
		if (str[i] == '-')
			tiray_case(tmp, i, j, tab, str);
		else if (str[i] == '$')
			dollar_case(i, j, tmp, str, tab);
		else if (str[i] == '"')
		{
			if (double_quote_case(i, j, tmp, flag, str, tab) != NULL)
				return (tab);
		}
		else if (str[i] == '\'')
		{
			if (simple_quote_case(i, j, tmp, flag, str, tab) != NULL)
				return (tab);

		}
		else if (str[i] != '\'' && str[i] != ' ' && str[i] != '\0')
		{
			if (others_case(&i, &j, &tmp, &flag, str, tab) != NULL)
				return (tab);
		}
		else
		{
			printf("pag\n");
			tab[j] = 0;
			return (tab);
		}
		if (flag == 1)
			i++;
	}
	printf("plouf\n");
	tab[j] = NULL;
	return (tab);
}