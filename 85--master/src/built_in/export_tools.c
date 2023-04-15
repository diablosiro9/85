/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:58:59 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/15 00:42:11 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/include.h"


void	write_fct(t_env *tmp, char *s1, int *i, int *flag, int fd)
{
	while (tmp)
	{
		if (ft_isalpha((int)tmp->name[0]) == 0)
			*flag = 1;
		// printf("on est la quand meme\n");
		if (tmp->name[0] == s1[*i])
		{
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(tmp->name, fd);
			if (tmp->content){
				ft_putstr_fd("=", fd);
				ft_putchar_fd('"', fd);
				ft_putstr_fd(&tmp->content[1], fd);
				ft_putchar_fd('"', fd);
			}
			ft_putchar_fd('\n', fd);
		}
		tmp = tmp->next;
	}
	*i = *i + 1;
}

void	alpha_export(t_env *env, int fd)
{
	char	*s1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char	*s2 = "abcdefghijklmnopqrstuvwxyz";
	int		i = 0;
	t_env	*tmp = env;
	int flag = 0;

	if (!env)
	{
		return ;
	}
	while (s1[i])
	{
		// printf("on est la quand meme\n");
		tmp = env;
		write_fct(tmp, s1, &i, &flag, fd);
		// while (tmp)
		// {
		// 	if (ft_isalpha(tmp->name[0]) == 0)
		// 		flag = 1;
		// 	// printf("on est la quand meme\n");
		// 	if (tmp->name[0] == s1[i])
		// 	{
		// 		ft_putstr_fd("declare -x ", fd);
		// 		ft_putstr_fd(tmp->name, fd);
		// 		if (tmp->content){
		// 			ft_putstr_fd("=", fd);
		// 			ft_putchar_fd('"', fd);
		// 			ft_putstr_fd(&tmp->content[1], fd);
		// 			ft_putchar_fd('"', fd);
		// 		}
		// 		ft_putchar_fd('\n', fd);
		// 	}
		// 	tmp = tmp->next;
		// }
		// i++;
	}
	if (flag == 1)
	{
		tmp = env;
		while (tmp)
		{
			if (ft_isalpha(tmp->name[0]) == 0)
			{
				ft_putstr_fd("declare -x ", fd);
				ft_putstr_fd(tmp->name, fd);
				if (tmp->content){
					ft_putstr_fd("=", fd);
					ft_putchar_fd('"', fd);
					ft_putstr_fd(&tmp->content[1], fd);
					ft_putchar_fd('"', fd);
				}
				ft_putchar_fd('\n', fd);
			}	
			tmp = tmp->next;
		}
	}
	i = 0;
	while (s2[i])
	{
		// printf("on est la quand meme\n");
		tmp = env;
		while (tmp)
		{
			if (ft_isalpha(tmp->name[0]) == 0)
				flag = 1;
			// printf("on est la quand meme\n");
			if (tmp->name[0] == s2[i] && tmp->name[0] != s1[i])
			{
				ft_putstr_fd("declare -x ", fd);
				ft_putstr_fd(tmp->name, fd);
				if (tmp->content){
					ft_putstr_fd("=", fd);
					ft_putchar_fd('"', fd);
					ft_putstr_fd(&tmp->content[1], fd);
					ft_putchar_fd('"', fd);
				}
				ft_putchar_fd('\n', fd);
			}
			tmp = tmp->next;
		}
		i++;
	}
}

void	print_export(t_env *env, int fd)
{
	t_env	*tmp;

	tmp = env;
	// printf("entre print export\n");
	alpha_export(tmp, fd);
}
