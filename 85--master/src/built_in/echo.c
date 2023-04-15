/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 21:21:13 by imac21            #+#    #+#             */
/*   Updated: 2023/04/15 00:41:46 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"


int	ft_isquote(int c)
{
	if (c == '"' || c == 39)
		return (1);
	return (0);
}

int	ft_isequal(int c)
{
	if (c == '=')
		return (1);
	return (0);
}

int	ft_iswspace(char c)
{
	while (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

void	help_echo(t_token *tmp, size_t *i, int *flag)
{
	if (tmp->value == NULL)
		return ;
	if (ft_strlen(tmp->value) == 3 && tmp->value[ft_strlen(tmp->value) - 1] == ' ')
	{
		if (tmp->next)
			tmp = tmp->next;
		else
		{
			*flag = 2;
			return ;
		}
		*flag = -1;
	}
	if (ft_strlen(tmp->value) > 3)
		return ;
	while (!ft_strncmp(tmp->value, "-n", ft_strlen("-n")))
	{
		if (tmp->next)
			tmp = tmp->next;
		else
		{
			*flag = 2;
			return ;
		}
		*flag = -1;
		while (g_data.cmd[*i] && ft_iswspace(g_data.cmd[*i]) != 1)
			*i += 1;
		while (g_data.cmd[*i] && ft_iswspace(g_data.cmd[*i]) == 1)
			*i += 1;
	}
}

int	echo_dollar(t_token **tmp)
{
	char	*stock = NULL;
	char	*test = NULL;

	if ((*tmp)->t_type == 4)
	{
		stock = (*tmp)->value;
		if (stock[1] == '$' && stock[2] == '?')
		{
			// printf("LA\n");
		}
		if (stock[1] == '$')
		{
			// printf("ui\n");
			test = search_env_content_do(g_data.env, &stock[2]);
			if (test == NULL)
				return (0);
			return (1);
		}
	}
	return (0);
}

int	case_quote(char *cmd, t_token **tmp, size_t *i, int redir)
{
	// int		idx = 0;
	char	*res = NULL;
	char	*stock = NULL;
	int		flag = 0;
	int		stop = 0;
	int		index = 0;

	(void)cmd;
	if ((*tmp)->t_type == 4 || (*tmp)->t_type == 5)
	{
		stock = (*tmp)->value;
		if ((*tmp)->t_type == 4)
		{
			// printf("laaaaaaaaa\n");
			// printf("echo_dollar(tmp) = %d\n", echo_dollar(tmp));
			if (echo_dollar(tmp) == 1)
			{
				stock = search_env_content_do(g_data.env, &stock[2]);
				// printf("sstock = %s\n", stock);
				if ((*tmp)->next)
				{
					flag = 0;
					stop = 1;
					ft_putstr_fd(stock, redir);
					(*tmp) = (*tmp)->next;
				}
				else
				{
					flag = 1;
					stop = 1;
					ft_putstr_fd(stock, redir);
				}
				// if (flag != 3)
				// 	ft_putstr_fd(stock, redir);
				return (flag);
			}
			else
			{
				stock = ft_substr((*tmp)->value, 1, ft_strlen((*tmp)->value) - 1);
				if (stock[ft_strlen(stock) - 1] == '"')
					stock = ft_substr((*tmp)->value, 1, ft_strlen((*tmp)->value) - 2);
				ft_putstr_fd(stock, redir);
				if ((*tmp)->next)
				{
					flag = 0;
					(*tmp) = (*tmp)->next;
				}
				else
					flag = 1;
				stop = 1;
				return (flag);
			}
		}
		if ((*tmp)->t_type == 5)
		{
			//printf("laaaaaaaaa\n");
			stock = &(*tmp)->value[1];
			res = malloc(sizeof(char *) * ft_strlen(stock) + 1);
			while (stock[index] && stock[index] != '\'')
			{
				res[index] = stock[index];
				index++;
			}
			res[index + 1] = '\0';
			if ((*tmp)->next)
			{
				flag = 3;
				ft_putstr_fd(res, redir);
				stop = 1;
			}
			else
			{
				flag = 1;
				stop = 1;
				ft_putstr_fd(res, redir);
			}
			free(res);
			if ((*tmp)->next)
			{	
				(*tmp) = (*tmp)->next;
				flag = 0;
			}
			else
				return (1);
			return (0);
		}
		//modif ligne den dessous si echo dikkae
		else if (flag != 0 && flag != 1)
			stock = &(*tmp)->value[1];
		i++;
	}
	// if (stop != 1)
	// 	ft_putstr_fd((*tmp)->value, redir);
	if (flag == 0)
	{
		// ft_putstr_fd((*tmp)->value, redir);
		return (0);
	}
	return (1);
}

int	case_string(char *cmd, t_token **tmp, size_t *i, int redir)
{
	int		idx = 0;
	char	*res = NULL;
	// printf("entre case string\n");
	// printf("Cmd = %s\n", cmd);
	// printf("tmp = %s et t_type = %d\n", (*tmp)->value, (*tmp)->t_type);
	if ((*tmp)->t_type == 6)
	{
		res = search_env_content_do(g_data.env, (*tmp)->value);
		ft_putstr_fd(res, redir);
		if ((*tmp)->next)
		{
			(*tmp) = (*tmp)->next;
			return (0);
		}
		else
			return (1);
	}
	else
	{
		while ((*tmp)->value[idx] && ft_iswspace((*tmp)->value[idx]) != 1)
		{
			ft_putchar_fd((*tmp)->value[idx++], redir);
		}
	}
	if ((*tmp)->next)
		(*tmp) = (*tmp)->next;
	else
		return (1);
	while (cmd[*i] && ft_isquote(cmd[*i]) != 1 && ft_iswspace(cmd[*i]) != 1
		&& ft_isprint(cmd[*i]) > 1 && cmd[*i] != '=')
		*i += 1;
	if (cmd[*i] == '=')
		*i += 1;
	return (0);
}

char	*reverse_search_env(t_env *env, char *name)
{
	int		i;
	char	*str;

	i = 0;
	str = name;
	while (i < g_data.env->num_vars && env)
	{
		if (!env)
			return (NULL);
		if (checking_str(env->content, str) == 1)
		{
			name = env->name;
			return (name);
		}
		env = env->next;
		i++;
	}
	return (NULL);
// int		i;
// 	char	*str;

// 	str = name;
// 	i = 0;
// 	printf("g_data.env->num_vars = %d\n", g_data.env->num_vars);
// 	while (i < g_data.env->num_vars)
// 	{
// 		if (env == NULL)
// 		{
// 			printf("env[i].name = %s\n", env[i].name);
// 			return (NULL);
// 		}
// 		if (search_env_content_check(str, env[i].content) == 1)
// 		{
// 			name = env[i].content;
// 			return (&name[1]);
// 		}
// 		i++;
// 	}
// 	return (NULL);
}


int	main_echo(char *cmd, t_token **tmp, size_t *i, int redir, int *flag)
{
	int		f_round = 0;
	int		index = 5;
	char	*stock = g_data.cmd;
	// char	*value = NULL;

	// printf("g_data.cmd = %s\n", g_data.cmd);
	if (*flag == -1)
	{
		(*tmp) = (*tmp)->next;
		if (stock[index] == '-' && stock[index + 1] == 'n')
		{
			index = index + 2;
			if (stock[index] && (stock[index] == ' ' || stock[index] == '\t' ))
			{
				while ((stock[index] == ' ' || stock[index + 1] == '\t') && stock[index])
					index++;
			}
		}
		// printf("stock + index = %s\n", stock + index);
	}
	// if ((*tmp)->value == NULL)
	// 	return (-1);
	// afftoken(*tmp, "null");
	// printf("i dans main_echo = %zu\n", *i);
	while ((*tmp))
	{
		if ((*tmp)->t_type == 4 || (*tmp)->t_type == 5)
		{
			index = index + ft_strlen((*tmp)->value);
			if (case_quote(cmd, tmp, i, redir) == 1)
				return (1);
			if (stock[index] == ' ' || stock[index - 1] == ' ')
				ft_putchar_fd(' ', redir);
		}
		if ((*tmp)->t_type == 3 && (*tmp)->t_type != 4 && (*tmp)->t_type != 5)
		{
			if (stock[index] == ' ')
				index++;
			index = index + ft_strlen((*tmp)->value);
			if (case_string(cmd, tmp, i, redir) == 1)
				return (1);
			if (stock[index] == ' ')
				ft_putchar_fd(' ', redir);
		}
		if ((*tmp)->t_type == 6 && (*tmp)->t_type != 4 && (*tmp)->t_type != 5)
		{
			// printf("tmp->Value = %s\n", (*tmp)->value);
			// printf("entre la\n");
			// printf("indx = %d\n", index);
			// printf("c = %c\n", stock[index]);
			// printf("stock[idx] = %c\n", stock[index]);
			if (stock[index] == '"')
				index = index + ft_strlen((*tmp)->value) + 2;
			else
				index = index + ft_strlen((*tmp)->value);
			// printf("indx = %d\n", index);
			// if (stock[index] == '"')
			// {
			// 	printf("yepaaaa\n");
			// 	index = index + 1;
			// }// if (stock[index] == ' ')
			// {
			// 	while (stock[index] == ' ')
			// 		index++;
			// }
			// if (stock[index] == '$')
			// {
			// 	while (stock[index] != ' ' && stock[index])
			// 		index++;
			// }
			if (case_string(cmd, tmp, i, redir) == 1)
				return (1);
			// printf("stock[index] = %c, index[] = %d\n", stock[index], index);
			if (stock[index] == ' ')
				ft_putchar_fd(' ', redir);
		}
		if ((*tmp)->t_type == 8 && (*tmp)->t_type != 4 && (*tmp)->t_type != 5)
		{
			index = index + ft_strlen((*tmp)->value);
			if (case_string(cmd, tmp, i, redir) == 1)
			{
				return (1);
			}
			if (stock[index] == ' ')
				ft_putchar_fd(' ', redir);
	
		}
		f_round = 1;
    }
	return (0);
}
// 	int	f_round = 0;
// 	printf("entre\n");
// 	if (*flag == -1)
// 		(*tmp) = (*tmp)->next;
// 	// if ((*tmp)->value == NULL)
// 	// 	return (-1);
// 	while ((*tmp))
// 	{
// 		if (ft_strcmp(cmd, "echo $?") == 0)
// 		{
// 			printf("echo $? = %d\n", g_data.exit);
// 			return (0);
// 		}
// 		if ((*tmp)->t_type == 4 || (*tmp)->t_type == 5)
// 		{
// 			if (case_quote(cmd, tmp, i, redir) == 1)
// 				return (1);
// 		}
// 		else if ((*tmp)->t_type == 3 && (*tmp)->t_type != 4 && (*tmp)->t_type != 5)
// 		{
// 			if (f_round != 0)
// 			// if ((*tmp)->t_type != 7)
// 				ft_putchar_fd(' ', redir);
// 			if (case_string(cmd, tmp, i, redir) == 1)
// 				return (1);
// 		}
// 		else if (((*tmp)->t_type == 8 || (*tmp)->t_type == 6) && (*tmp)->t_type != 4 && (*tmp)->t_type != 5)
// 		{
// 			if (case_string(cmd, tmp, i, redir) == 1)
// 				return (1);
// 		}
// 		f_round = 1;
//         // printf("milieu loop\n");
//     }
// 	// if ((*tmp)->t_type == 6)
// 	// {
// 	// 	ft_putstr_fd()
// 	// }
//     // printf("fin loop\n");
// 	return (0);

// int	checking_full_n()
// {
	
// }

int	ft_echo(int redir)
{
	t_token 	*tmp;
	char		*cmd;
	size_t			i;
	int			flag;

	flag = 1;
	i = 0;
	tmp = g_data.token;
    cmd = g_data.cmd;
	// printf("entre echo\n");
	if (redir == -1)
		redir = 1;
    while (i < ft_strlen("echo"))
		i += 1;
	if (tmp->next)
		tmp = tmp->next;
	else
	{
		flag = 1;
		ft_putchar_fd('\n', redir);
		return (1);
	}
	// printf("la\n");
	help_echo(tmp, &i, &flag);
	if (flag == 2)
		return (1);
	// printf("avant main_Echo\n");
	main_echo(cmd, &tmp, &i, redir, &flag);
	if (flag == 1)
		ft_putchar_fd('\n', redir);
	return (1);
}
