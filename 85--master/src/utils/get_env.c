/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:06:38 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/10 15:49:35 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

// Mimi - Renommination pour claireté (de starter_env à get_env_starter)
unsigned int	get_env_starter(char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

// Quasiment parfaitement propre (check malloccc)
t_env	*get_env(char **env)
{
	int		i;
	t_env	*list;

	i = 0;
	list = malloc(sizeof(t_env) * 100);
	if (!list)
	{
		printf("Error : malloc() failed.\n");
		exit(-127);
	}
	while (env[i])
	{
		list[i].name = ft_strsub(env[i], 0, ft_strchr(env[i], '=') - env[i]);
		list[i].content = ft_strsub(env[i], get_env_starter(env[i]), \
			ft_strlen(env[i]) - (ft_strchr(env[i], '=') - env[i]));
		i++;
	}
	list->num_vars = i;
	return (list);
}

char **get_env_bis(t_env *env)
{
    int i = 0;
    char **tab = (char **)malloc(sizeof(char *) * 10000);
    while (i < g_data.env->num_vars)
    {
        tab[i] = ft_strjoin(env->name, env->content);
		env = env->next;
        i++;
    }
    tab[i] = NULL;
	return (tab);
}