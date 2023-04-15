/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:09:03 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/12 14:45:11 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

static int	ft_nbr_str(char *s, char c)
{
	unsigned int	i;
	unsigned int	nbr;

	i = 0;
	nbr = 0;
	while (s[i])
	{
		if (*s == '\0')
			break ;
		else if (s[i] != c)
		{
			nbr++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (nbr);
}

static char	*ft_strndup(char const *s, size_t n)
{
	char	*stmp;
	size_t	i;

	i = 0;
	stmp = (char *)malloc(n + 1);
	if (stmp == NULL)
		return (NULL);
	while (i < n)
	{
		stmp[i] = s[i];
		i++;
	}
	stmp[i] = '\0';
	return (stmp);
}

char	**ft_oldsplit(char const *s, char c)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;
	char			**tab;

	tab = malloc((sizeof(char *)) * (ft_nbr_str((char *)s, c) + 1));
	if (!s || !(tab))
		return (NULL);
	i = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		j = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > j)
			tab[k++] = ft_strndup(s + j, i - j);
	}
	tab[k] = NULL;
	return (tab);
}

void	*get_cmd_file(char *cmd)
{	
	int		i;
	char	*path;
	char	**tab_path;
	char	*tmp1;
	char	*tmp2;

	i = 0;
	path = search_env_content_do(g_data.env, "$PATH");
	if (path == NULL)
		return (NULL);
	tab_path = ft_oldsplit(path, ':');
	while (tab_path[i])
	{

		tmp1 = ft_strjoin_bis(tab_path[i], "/");
		tmp2 = ft_strjoin_bis(tmp1, cmd);
		free(tmp1);
		if (access(tmp2, X_OK) == 0)
		{
			// free_tab(tab_path);
			ft_tab_delete(tab_path);
			return (tmp2);
		}
		free(tmp2);
		i++;
	}
	ft_tab_delete(tab_path);
	return (ft_strdup(cmd));
}

void	*split_cmd_file()
{
	t_token	*tmp;
	char	*path;
	char	**tab_path;
	char	**tmp1;
	int		i[2];

	i[1] = 0;
	path = NULL;
	tmp = g_data.token;
	tmp1 = malloc(sizeof(char *) * 2 + 1);
	// printf("cmd = %s\n", cmd);
	// if (cmd == NULL)
	// {
		while (tmp)
		{
			if (tmp->t_type == 3 && i[1] != 1)
			{
				if (strcmp(tmp->value, "unset") == 0)
				{
					tmp->t_type = COMMAND;
					break ;
				}
				path = search_env_content_do(g_data.env, "$PATH");
				if (path == NULL)
					return (NULL);
				tab_path = ft_oldsplit(path, ':');
				path = tmp->value;
				i[0] = 0;
				while (tab_path[i[0]])
				{
					tmp1[0] = ft_strjoin_bis(tab_path[i[0]], "/");
					tmp1[1] = ft_strjoin_bis(tmp1[0], path);
					free(tmp1[0]);
					if (access(tmp1[1], X_OK) == 0)
					{
						tmp->t_type = COMMAND;
						i[1] = 1;
						tmp->value = tmp1[1];
						break ;
					}
					free(tmp1[1]);
					i[0]++;
				}
				free(tab_path);
				// ft_tab_delete(tab_path);
			}
			if (tmp->t_type == 0)
				i[1] = 0;
			tmp = tmp->next;
		}
		free(tmp1);
		free(path);
		return ((void *)g_data.token->value);
}
	// tmp1[1] = get_cmd_file(cmd);
	// if (access(tmp1[1], X_OK) == 0)
	// {
	// 	tmp->t_type = COMMAND;
	// 	tmp->value = tmp1[1];
	// 	// free_tab(tab_path);
	// 	// ft_tab_delete(tab_path);
	// 	return (tmp);
	// }
	// return (get_cmd_file());
// }
