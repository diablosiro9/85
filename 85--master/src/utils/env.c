/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:56:29 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/14 19:32:58 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

/*
    Mimi
    Les fonctions starter_env et get_env se trouvaient dans le main
    Par soucis de rangement et de normes, je les mets dans ce fichiers
    ./src/utils/env.c dédié entièrement aux fonctions pour l'environnement 

*/

int	search_env_content_check(char *ref, char *find)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (!ref || !find)
		return (0);
	if (!ref && !find)
		return (0);
	while (ref[i])
	{
		if (ref[i] != find[j])
			return (0);
		i++;
		j++;
	}
	return (1);
}

char	*search_env_content(t_env *env, char *name)
{
	int		i;
	char	*str;

	str = name;
	i = 0;
	while (i < g_data.env->num_vars)
	{
		if (env[i].name == NULL)
		{
			return (NULL);
		}
		if (search_env_content_check(env[i].name, str) == 1)
		{
			name = env[i].content;
			return (&name[1]);
		}
		i++;
	}
	return (NULL);
}

int	checking_str(char *ref, char *find)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!ref || !find)
		return (0);
	while (ref[i])
	{
		if (find[j] == '$')
			j++;
		if (ref[i] != find[j])
			return (0);
		i++;
		j++;
	}
	return (1);
}

char	*search_env_content_do(t_env *env, char *name)
{
	int		i;
	char	*str;

	i = 0;
	str = name;
	while (i < g_data.env->num_vars && env)
	{
		if (env->name == NULL || !env)
			return (NULL);
		if (checking_str(env->name, str) == 1)
		{
			name = env->content;
			return (&name[1]);
		}
		env = env->next;
		i++;
	}
	return (NULL);
}
