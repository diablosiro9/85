/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 14:32:59 by mla-rosa          #+#    #+#             */
/*   Updated: 2023/04/15 20:51:56 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"
// #include <readline/readline.h>
// #include <readline/history.h>
/*
	DOOODOOOOOOO	MEHDI
   Mimi 
	Je t'ai tout mis dans des dossiers et fichiers .c logiques
	pour améliorer la lisibilié et la claireté du code (et bien
	evidemment pour la norme)
	
	De plus, par convention faudra mettre ton main seul dans le fichier 
	main.c et déplacer les autres fonctions ci-dessous dans d'autres fichiers,
	comme je viens de faire

	Les fonctions qui était dans se .c et ./src/utils.c se trouvent :
	./src/utils/aff.c
		-> void afflist(t_list *list, char *name)
		-> void afftab(char **tab)
		-> void afftoken(t_token *list, char *name)
	./src/utils/env.c
		-> unsigned int	get_env_starter(char *s) nommé env_starter avant
		-> t_env *get_env(char **env)
		-> int	search_env_content_check(char *ref, char *find) nommé checking_str avant
		-> char	*search_env_content(t_env *env, char *name)
	./src/utils/list.c
		-> t_list *ft_lstadd(t_list **alst, t_list *new)
	./src/utils/str.c
		-> void ft_putstr(char *str)
		-> char *ft_strsub(char const *s, unsigned int start, size_t len)
*/

int main(int ac, char **av, char **env)
{
	t_list	*history = NULL;
    t_list *list = NULL;
	t_list	*res = NULL;
	char	*tmp = NULL;
	


	(void)ac;
    (void)av;
	history = ft_lstnew(NULL);
    g_data.env = get_env_do(env);
	(void)res;
    while (42)
	{
		g_data.cmd = ft_strdup(readline("minishell>"));
		if (g_data.cmd == NULL) 
            sig_quit(3);
		tmp = g_data.cmd;
		add_history(g_data.cmd);
		if (g_data.cmd != NULL && ft_strlen(g_data.cmd) > 0)
		{
			printf("la\n");
			if (checking_closed(g_data.cmd) != 0 && checking_closed(g_data.cmd) != -1)
 	    	{
				list = ft_lexer(g_data.cmd);
				if (list != NULL)
				{
					ft_exec(ft_parsor(list));
					// ft_list_delete(&list);
				}
			}
			ft_token_delete(&g_data.token);
		}
		free(g_data.cmd);
		g_data.cmd = NULL;
	}
    return (0);
}
