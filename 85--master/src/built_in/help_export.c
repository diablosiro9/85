/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:28:30 by dojannin          #+#    #+#             */
/*   Updated: 2023/03/28 11:57:55 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

t_env	*ft_lstnew_env(char *name, char *content)
{
	t_env	*new;

	if (name == NULL)
		return (NULL);
	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->name = name;
	new->next = NULL;
	new->num_vars = 0;
	return (new);
}

void	print_export(t_env *env, int fd);

int	ft_lstadd_back_env(t_env **alst, t_env *new)
{
	t_env	*temp = NULL;

	if (!new || new->name == NULL)
		return 0;
	if (!*alst)
	{
		*alst = new;
		return 1;
	}
	else
	{
		temp = *alst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
	return 1;
}

char	*ft_strjoin_w(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen((char *)s1)
				+ ft_strlen((char *)s2) + 1));
	if (str == NULL)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

int	check_str(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s2[i] != '\0')
		return (0);
	return (1);
}

int	ft_same_content(char *name, char *content)
{
	t_env	*tmp;

	tmp = g_data.env;
	while (tmp)
	{
		if (!ft_strncmp(name, tmp->name, ft_strlen(tmp->name)))
		{
			if (!ft_strncmp(content, tmp->content, ft_strlen(content)))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}