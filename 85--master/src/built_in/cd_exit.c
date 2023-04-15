/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 16:34:36 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/15 01:42:32 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

/*
	echo et l’option -n
◦ cd uniquement avec un chemin relatif ou absolu
◦ pwd sans aucune option
◦ export sans aucune option
◦ unset sans aucune option
◦ env sans aucune option ni argument
◦ exit sans aucune option
*/


// SI LANCEMENT DU MINISHELL ON VIRE JUSTE AVANT LANCEMENT L'ENV AVEC UN UNSET, LE MINISHELL DOIT SE TROUVER OU CREER UN ENV,
// UN PWD, OU UN OLD_PWD, ET UN HOME POUR TENIR LA ROUTE, AINSI QUE DES PATH. Fixer avant l'env

//ECHO SEC ➜ 
//  Back_to_F git:(main) ✗ echo test | cat -e
// test$
// ➜  Back_to_F git:(main) ✗ echo -n test | cat -e
// test%                              

void	ft_exit(int nb)
{
	g_data.exit = nb;
	//Limite de 255 comme valeur de retour, apres faire des modulos pour "fit" par rapport a 255 (un cas tricky a veri aupres de max)
	if (!nb)
	{	
		printf("exit\n");
		exit(1);
	}
	else
	{
		printf("exit\n");
		if (nb > 255)
			exit(nb % 255);
		else
			exit(nb);
	}
}

void	change_env_content(char *name, char *new)
{
	t_env *tmp = NULL;

	tmp = g_data.env;
	while (tmp)
	{
		if (strcmp(tmp->name, name) == 0)
			tmp->content = ft_strdup(new);
		tmp = tmp->next;
	}
}

int	back_path(char *str)
{
	int	i = 0;

	while (str[i])
		i++;
	if (str[0] == '.' && str[1] == '.' && str[2] == '\0')
		return (1);
	if (str[i - 1] == '.' && str[i - 2] == '.' 
		&& (str[i - 3] == '/' || str[i - 3] == ' '))
		return (1);
	return (0);
}

char	*cut_pwd(char *str)
{
	int	i = 0;
	int	stock = 0;
	char	*tmp = NULL;
	while (str[i])
		i++;
	while (str[i] != '/')
		i--;
	if (str[0] != '/')
	{
		tmp = malloc(sizeof(char) * i + 2);
		tmp[0] = '/';
		stock = 1;
		while (stock < i + 1)
		{
			tmp[stock] = str[stock - 1];
			stock++;
		}
	}
	else
	{
		tmp = malloc(sizeof(char) * i + 1);
		while (stock < i)
		{
			tmp[stock] = str[stock];
			stock++;
		}
	}
	tmp[stock] = '\0';
	return (tmp);
}

void	ft_cd(char *path)
{
	char	*res;
	res = search_env_content_do(g_data.env, "$PWD");
	char	pwd[1000];
	char	*tmp = NULL;
	
	printf("res = %s\n", res);
	if (back_path(path) == 1)
		path = cut_pwd(res);
	if (!path || strcmp(path, "$HOME") == 0)
		chdir(search_env_content_do(g_data.env, "$HOME"));
	printf("path == %s\n", path);
	if (access(path, F_OK) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putchar_fd(':', STDERR_FILENO);
		ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
		g_data.exit = 126;
	}
	else if (chdir(path) == -1)
	{
		printf("la\n");
		if (access(ft_strjoin(res, path), X_OK) == -1)
		{
			printf("0.1\n");
			ft_putstr_fd("cd: ", STDERR_FILENO);
			ft_putstr_fd(path, STDERR_FILENO);
			ft_putchar_fd(':', STDERR_FILENO);
			ft_putstr_fd("  No such file or directory\n", STDERR_FILENO);
			g_data.exit = 126;	
		}
		else if (chdir(ft_strjoin(res, path)) == -1)
		{
			printf("0.2s\n");
			ft_putstr_fd("cd: ", STDERR_FILENO);
			ft_putstr_fd(path, STDERR_FILENO);
			ft_putchar_fd(':', STDERR_FILENO);
			ft_putstr_fd("Permission denied\n", STDERR_FILENO);
		}
		
	}
	tmp = getcwd(pwd, sizeof(pwd));
	change_env_content("PWD", tmp);
	res = search_env_content_do(g_data.env, "$PWD");
}


unsigned int	starter_env(char *s)
{
	unsigned int	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}




/* Obtenir l'env grace a la struct global et le print dans un tmp. Parcourir jusquau bout. 
	Cette fonction doit etre lance avant l'exec generale (builtin tricky)
		->Si possible obtenir les cmd des le debut, identifier les redir, gerer les fd pour l'entree, 
		identifier le reste des builtins tricky et return en fonction
		Sinon lancer pleinement l'exec avec les param need (redir determinee (INT), cmd (CHAR **), fd[0])
			->fd[0] correspond au file d'entree, redir a notre sortie, 
	Dans la fonction exec on reverifie les builtins, puis les path de la dite cmd,\
	dup2(fd, stdin_fileno), dup redir stdout si elle est valablem un tmp prendra le path de cmd[0]
	Execv tout ca dans un fork, close les fd et redir, waitpid, return;
*/

// void	check_exec()
// {
// 	t_token	*tmp = NULL;
	
// 	tmp = g_data.token;
// }