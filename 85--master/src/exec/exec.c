/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:03:26 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/15 20:01:23 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

void	exec_hd(char **new_arg, char **av)
{
	char	**argv = NULL;
	int fd[2];
	int	i = 0;
	
	if (pipe(fd) == -1) {
      exit(1);
	}
	pid_t pid = fork();
  	if (pid == 0) {
		close(fd[0]);
		while (new_arg[i])
		{
			write(fd[1], new_arg[i], strlen(new_arg[i]));
			if (strlen(new_arg[i]) > 0)
				write(fd[1], "\n", 1);
			i++;
		}
		close(fd[1]);
		exit(0);
 	}
  	else
  	{
   		close(fd[1]);
    	dup2(fd[0], STDIN_FILENO);
		argv = fill_hd_arg(split_cmd_file(av[0]), av[0]);
    	execve(split_cmd_file(av[0]), argv, NULL);
    	exit(1);
  	}
}

void	check_heredoc(t_list *stock, char **new_arg, char **argv)
{
	if (det_nb_hd() == 1 || det_nb_hd() == 2)
	{
		stock = simple_hd();
		if (stock == NULL)
			stock = ft_lstnew("");
		new_arg = ft_exec_args(stock);
		exec_hd(new_arg, argv);
	}
}

void    ft_exec_command(char *cmd_file, char **argv) {
    
	t_list	*stock = NULL;
	char	**new_arg = NULL;
    // Exécuter la commande avec execve
	// printf("cmd_file = %s\n", argv[0]);
    if (cmd_file == NULL)
        cmd_file = split_cmd_file(argv[0]);
	if (det_hd() == 1)
		check_heredoc(stock, new_arg, argv);
	printf("a\n");
    if (execve(cmd_file, argv, get_env_bis(g_data.env)) == -1) {
		printf("biz\n");
        printf("minishell: %s: command not found\n", argv[0]);
        exit(EXIT_FAILURE);
    }
	printf("bs\n");
	// printf("estimaetion fausse\n");
    // Nous ne devrions jamais arriver ici
    exit(EXIT_SUCCESS);
}

char **ft_exec_args(t_list *str)
{
    int i = 0;
    int argc = 0;
    char **argv = NULL;
    // t_list *current = str;

	(void)str;
	t_token *current = g_data.token;
    // Compter le nombre d'arguments
    while (current != NULL) {
        argc++;
        current = current->next;
    }
    
    // Créer un tableau d'arguments
    argv = (char **)malloc(sizeof(char *) * (argc + 1));
    current = g_data.token;
    while (current != NULL) {
        argv[i] = current->value;
        i++;
        current = current->next;
    }
    argv[i] = NULL; // Dernier élément doit être NULL
    return (argv);
}

// Nous sommes dans le processus parent
int ft_exec_proc(pid_t pid)
{
    g_data.exit = WEXITSTATUS(g_data.exit);
    // printf("exit = %d\n", g_data.exit);

    waitpid(pid, &g_data.exit, 0);
    if (WIFEXITED(g_data.exit)) {
        int exit_status = WEXITSTATUS(g_data.exit);
        return exit_status;
    } 
    return (-1);
}


int ft_exec(t_list *str) {
    char **argv = ft_exec_args(str);


    // afflist(str, "what\n");
	afftoken(g_data.token, "cqcq");
	// printf("str->value = %s\n", (char *)str->content);
	if (det_builtin() == 1)
		return (1);
	if (det_hd() == -1)
		return (0);
	// printf("arrive mehdi part\n");
    if (ft_redir_detec_right(str) >= 1)
        ft_redir_right(str);
    if (ft_redir_detec_left(str) >= 1)
        ft_redir_left(str);
    if (ft_pipe_detec(str) == 0)
    {
        if (g_data.token->t_type == PIPE && g_data.token->next == NULL) {
            printf("minishell: syntax error near unexpected token `|'\n");
            g_data.exit = 258;
            return (258);
        }
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            return -1;
        }
        else if (pid == 0)
            ft_exec_command(NULL, argv);
        else
            return (ft_exec_proc(pid));
    }
    if (ft_pipe_detec(str) > 0)
        ft_pipe(str);
    return 0;
}

