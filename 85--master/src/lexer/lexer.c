/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:04:10 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/15 21:08:54 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

/*
    Mimi
    Déplacement de la fonction lexer dans le dossier/.c dédié ./src/lexer/lexer.c
    simplement par claireté et norme

*/
void	ft_tab_delete(char **tab)
{
	// char	*tmp;
	int		i;

	i = 0;
	while (tab[i] != NULL)
	{
		// printf("tab[i] = %s\n", tab[i]);
		// tmp = tab[i];
		// tab[i] = tab[i + 1];
		free(tab[i]);
		i++;
	}
	free(tab);
}

// static int	ft_check_c(char s, char c)
// {
// 	if (s == c)
// 		return (1);
// 	return (0);
// }

// static int	count_char_c(const char *s, char c)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	while (s[i])
// 	{
// 		while (s[i] && ft_check_c(s[i], c) == 1)
// 			i++;
// 		if (s[i] && ft_check_c(s[i], c) == 0)
// 		{
// 			count++;
// 			while (s[i] && ft_check_c(s[i], c) == 0)
// 				i++;
// 		}
// 	}
// 	return (count);
// }

// static char	*ft_alloc_str(char const *s, char c)
// {
// 	char	*tab;
// 	int		i;

// 	i = 0;
// 	while (s[i] && ft_check_c(s[i], c) == 0)
// 		i++;
// 	tab = malloc(sizeof(char) * (i + 1));
// 	if (tab == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (s[i] && ft_check_c(s[i], c) == 0)
// 	{
// 		tab[i] = s[i];
// 		i++;
// 	}
// 	tab[i] = '\0';
// 	return (tab);
// }

static int	check_c(char s, char c)
{
	if (s == c)
		return (1);
	return (0);
}

static int	count_c(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && check_c(s[i], c) == 1)
			i++;
		if (s[i] && check_c(s[i], c) == 0)
		{
			count++;
			while (s[i] && check_c(s[i], c) == 0)
				i++;
		}
	}
	return (count);
}

static char	*alloc_str(char const *s, char c)
{
	char	*tab;
	int		i;

	i = 0;
	while (s[i] && check_c(s[i], c) == 0)
		i++;
	tab = malloc(sizeof(char) * (i + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (s[i] && check_c(s[i], c) == 0)
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

char	**ft_split_do(char const *s, char c)
{
	size_t		i;
	int		nb_c;
	char	**dst;

	i = 0;
	printf("s = %s\n", s);
	nb_c = count_c(s, c);
	printf("nb_c = %d\n", nb_c);
	dst = (char **)malloc(sizeof(char *) * (nb_c + 1) + 1);
	if (dst == NULL)
		return (NULL);
	nb_c = 0;
	printf("la\n");
	while (i < ft_strlen(s) && s[i])
	{
		printf("i = %zu\n", i);
		while (s[i] && check_c(s[i], c) == 1)
			i++;
		if (s[i] && check_c(s[i], c) == 0)
		{
			printf("la ca va\n");
			dst[nb_c] = alloc_str((s + i), c);
			printf("dest  = %s et nb_c = %d\n", dst[nb_c], nb_c);

			nb_c++;
			printf("i = %zu\n", i);

			while (s[i] && check_c(s[i], c) == 0)
				i++;
			printf("i = %zu\n", i);
			printf("fin\n");
			
		}
	}
	printf("sors\n");
	printf("nb_c = %d\n", nb_c);
	dst[nb_c] = 0;
	printf("fin\n");
	return (dst);
}

t_list	*ft_lexer(char *str)
{
	int		i;
	t_list	*list;
	char	**tab = NULL;
	char	*stock = NULL;

	i = 0;
	list = NULL;
	printf("lexer\n");
	printf("ft_strlen(str) = %zu\n", ft_strlen(str));
	tab = ft_split_do(str, ' ');
	afftab(tab);
	// printf("fin lexer\n");
	if (!tab)
	{
		printf("Error : malloc failed() in ft_lexer.");
		exit (0);
	}
	while (tab[i])
		i++;
	printf("TAILLE TAB = %d\n", i);
	i = 0;
	while (tab[i] != NULL)
	{
		stock = tab[i];
		printf("tab[i] = %s\n", tab[i]);
		ft_lstadd(&list, ft_lstnew(stock));
		i++;
	}
	printf("taab[] = %s\n", tab[i]);
	// ft_tab_delete(tab);
	// free(tab);
	// printf("tab[i] = %s\n", tab[i]);
	tokenizateur(list, i);
	recuperator();
	modificator();
	afftoken(g_data.token, "lexer");

	if (terminator() == NULL)
		return (NULL);
	// for (t_token *tmp = g_data.token; tmp; tmp = tmp->next)
	// 	printf("type = %d, value = %s\n", tmp->t_type, tmp->value);
	if (reunificator() == NULL)
		return (NULL);
	printf("uiii\n");
	// afflist(list, "lexer");
	afftoken(g_data.token, "lexer");
	free(tab);
	return (list);
}
