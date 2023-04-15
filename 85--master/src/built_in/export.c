/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 09:15:59 by imac21            #+#    #+#             */
/*   Updated: 2023/04/15 15:10:07 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

int	skip(char **new_env, size_t *i, t_token **tmp, char *cmd)
{
	while (ft_iswspace(cmd[*i]))
		*i += 1;
	if (*i == ft_strlen(g_data.cmd))
		return (-1);
	if (cmd[*i] && ft_isquote(cmd[*i]) == 1)
		*i += 2;
	if ((*tmp)->next)
		(*tmp) = (*tmp)->next;
	*new_env = ft_strdup((*tmp)->value);
	*i += ft_strlen(*new_env);
	return (0);
}

int	env_exist(char *name)
{
	t_env	*tmp;

	tmp = g_data.env;
	// printf("la===n\n");
	// printf("name = |%s|\n", name);
	while (tmp)
	{
		if (check_str(name, tmp->name) == 1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	change_env(char *new_env, char *content)
{
	if (env_exist(new_env) == 0)
		ft_lstadd_back_env(&g_data.env,
			ft_lstnew_env(ft_strdup(new_env), ft_strdup(content)));
	else if (ft_same_content(new_env, content) != 1)
		cmd_unset_assist(new_env, content);
	if (new_env)
		free(new_env);
	if (content)
		free(content);
}

char	*reverse_chr(char *s, char c)
{
	int		i = 0;
	char	*res = NULL;

	while (s[i] && s[i] != c)
		i++;
	res = malloc(sizeof(char) * i + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return res;
}

int	help_export(t_token **tmp, size_t *i, int redir)
{
	if (redir == -1)
		redir = 1;
	while (*i < ft_strlen("export"))
		*i += 1;
    if (!(*tmp)->next)
	{
		// printf("help_export\n");
		print_export(g_data.env, 1);
		return (0);
	}
	// if (!(*tmp)->next || (*tmp)->next->t_type == 6
	// 	|| (*tmp)->next->t_type == 8)
	// {
	// 	print_export(g_data.env, 1);
	// 	return (0);
	// }
	// (*tmp) = (*tmp)->next;
	return (1);
}

void	unset_assist(char *name)
{
	t_env	*env;
	t_env	*start;

	start = g_data.env;
	env = g_data.env;
	if (!name)
		return ;
	while (env)
	{
		if (check_str(name, env->name) == 1)
		{
			free(env->content);
			env->content = NULL;
			break ;
		}
		env = env->next;
	}
	g_data.env = start;
}


void	cmd_unset_assist(char *name, char *content)
{
	t_env	*env;
	t_env	*start;
	int		flag = 0;

	start = g_data.env;
	env = g_data.env;
	if (!name)
		return ;
	printf("content = %s\n", content);
	printf("name == |%s|\n", name);
	while (env)
	{
		if (check_str(name, env->name) == 1)
		{
			if (env->content == NULL)
				flag = 1;
			//free(env->content);
			env->content = NULL;
			if (content != NULL)
				env->content = ft_strdup(content);
			else
			{
				if (flag != 1)
					env->content = ft_strdup("""");

			}
			break ;
		}
		env = env->next;
	}
	g_data.env = start;
}

int	main_export(char *content, char *new_env, t_token *tmp, size_t i)
{
	int z = 0;
	int	flag = 0;
	afftoken(tmp, "export");
	// printf("main_Export\n");
	(void)content;
	while (tmp)
	{
		if (z == 1)
			return 1;
		if (skip(&new_env, &i, &tmp, g_data.cmd) == -1)
			return (1);
		// if (g_data.cmd[i] && tmp && ft_iswspace(g_data.cmd[i]) == 1)
		// {
			// printf("entre au pire endroit du monde\n");
        //     if (new_env)
		//     	free(new_env);
		// }
    	if (tmp && tmp->value[0] == 0)
        {
			// printf("tes fou\n");
			while (g_data.cmd[i] && ft_iswspace(g_data.cmd[i]) != 1)
            i += 1;
            if (tmp->next)
            tmp = tmp->next;
        }
		while (tmp){
			printf("tmp->value = %s\n", tmp->value);
			if (ft_strcmp("export", tmp->value) == 0)
				tmp = tmp->next;
			// printf("new_env == %s\n", new_env);
			if (tmp->value[0] == '=')
				return (0);
			if (tmp->t_type == 4 || tmp->t_type == 5)
			{
				new_env = &tmp->value[1];
				flag = ft_strlen(tmp->value);
				// printf("FLAG == %d\n", flag);
				while (flag != 0 && (new_env[flag - 1] != '\'' && new_env[flag - 1] != '"'))
					flag--;
				// printf("FLAG == %d\n", flag);
				if (flag == (int)ft_strlen(tmp->value))
					new_env[flag] = '\0';
				new_env[flag - 1] = '\0';
			}
			if (env_exist(reverse_chr(new_env, '=')) == 0)
			{
				printf("env existe pas\n");
				printf("(reverse_chr(new_env, '=') = %s\n", reverse_chr(new_env, '='));
				printf("ft_strrchr(new_env, '=')) = %s\n", ft_strrchr(new_env, '='));
				
	       		if (ft_lstadd_back_env(&g_data.env, ft_lstnew_env((reverse_chr(new_env, '=')), ft_strrchr(new_env, '='))) == 0)
					ft_lstadd_back_env(&g_data.env, ft_lstnew_env(new_env, " "));
			}
			else
			{	
				printf("new_env == %s dans le cas ou env.name existe \n", new_env);
				cmd_unset_assist(reverse_chr(new_env, '='), ft_strrchr(new_env, '='));
			}
			// printf("fin premiere tache\n");
			printf("entre dans lendroit sombre\n");
			if (tmp->next){
				tmp = tmp->next;
			new_env = ft_strdup(tmp->value);
			printf("new_env = %s\n", new_env);
			}
			else
				return (1);
		}
		// printf("content == %s\n", content);
		// printf("fin boucle\n"); 
		// if (ft_same_content(new_env, content) != 1)
		// {
			// printf("2e endroit maudit\n");
        //     cmd_unset_assist(new_env, content);
		// }
		// printf("uiiiii\n");
	    // if (new_env)
        //     free(new_env);		
        // if (content)
        //     free(content);
		z++;
	}
	// printf("sorti cash\n");
	return (1);
}

int	ft_export(int redir)
{
	t_token		*tmp;
	size_t			i;
	char		*new_env;
	char		*content;

	content = g_data.cmd;
	new_env = NULL;
	i = 0;
	tmp = g_data.token;
	if (help_export(&tmp, &i, redir) == 0)
		return (0);
	// printf("kakakak\n");
	if (main_export(content, new_env, tmp, i) == 1)
	{
		g_data.export = g_data.env;
		return (1);
	}
	return (1);
}