/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:47:55 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/04 13:54:01 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

/*
    Mimi
    Déplacement de la fonction influencant sur une string dans le 
    dossier/.c dédié ./src/utils/str.c simplement par claireté et norme
*/

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin_bis(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;
	int		size;

	i = -1;
	j = 0;
	size = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (size));
	if (str == NULL)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}
