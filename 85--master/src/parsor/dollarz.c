/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarz.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:23:09 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/15 00:44:33 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

void	*find_all_dollars(void)
{
	t_token	*tmp;
	char *cmd;

	tmp = g_data.token;
	cmd = g_data.cmd;
	// printf("cmd = %s\n", cmd);
	if (tmp)
	{
		// printf("on est la\n");
		while (tmp)
		{
			if (ft_strcmp(cmd, "echo $?") == 0)
			{
				return ((void *)g_data.token->value);
			}
			if (tmp->t_type == 6)
			{
				// printf("tmp->value = %s\n", tmp->value);
				if (ft_strlen(tmp->value) <= 1)
					// tmp->value = search_env_content_do(g_data.env, tmp->value);
				// else
					printf("Us_Bash: $: command not found\n");
			}
			tmp = tmp->next;
		}
	}

	return ((void *)g_data.token->value);
}
