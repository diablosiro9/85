#include "../../include/include.h"

int ft_pipe_detec(t_list *str)
{
    int i = 0;
    // t_list *current = str;
	t_token	*current = g_data.token;
	(void)str;
    while (current->next != NULL)
    {
        if (ft_strcmp((char *)current->value, "|") == 0)
            i++;
        current = current->next;
    }
    return (i);
}

int ft_pipe_argv_size(t_token *tmp)
{
    int count = 0;

    while(tmp && tmp->t_type != 0)
    {
        count++;
        tmp = tmp->next;
    }
    return (count);
}

char **ft_pipe_argv(t_token *token)
{
    // printf("ICI");
    int i = 0;
    char **argv = NULL;
    t_token *tmp = token;
    int size = ft_pipe_argv_size(tmp);

    if (!(argv = malloc(sizeof(char *) * (size + 1)))) {
        perror("malloc");
        exit (-1);
    }
    while(tmp && tmp->t_type != 0)
    {
        if (!(argv[i] = ft_strdup(tmp->value))) {
            perror("malloc");
            exit (-1);
        }
        tmp = tmp->next;
        i++;
    }
    argv[i] = NULL;
    return (argv);
}

int ft_pipe_exec(char *cmd, char **argv, int pid_nb, int pid_idx)
{
    int fds[3];
    int status = 0;
    pid_t pid = 0;
    static int fd = STDIN_FILENO;

	// printf("cmd = %s\n", cmd);
    pipe(fds);
    if ((pid = fork()) == -1)
        perror("fork");
    else if (pid == 0) {
        dup2(fd, STDIN_FILENO);
        if (pid_idx < pid_nb)
            dup2(fds[1], STDOUT_FILENO);
        if (execve(cmd, argv, get_env_bis(g_data.env)) == -1) {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            if (pid_idx < pid_nb)
                close(fds[1]);
            if (fd != STDIN_FILENO)
                close(fd);
            fd = fds[0];
            return WEXITSTATUS(status);
        }
    }
    if (pid_idx < pid_nb)
        close(fds[1]);
    if (fd != STDIN_FILENO)
        close(fd);
    fd = fds[0];
    return (0);

}

int ft_pipe(t_list *list)
{
    g_data.list = list;
    int pid_idx = 0;
    int pid_nb = ft_pipe_detec(list);
    int status = 0;
    t_token *tmp = g_data.token;

    while (tmp) {
        if (tmp->t_type != 0 && tmp->t_type != 7) {
            status = ft_pipe_exec(tmp->value, ft_pipe_argv(tmp), pid_nb, pid_idx);
            pid_idx++;
        }
        tmp = tmp->next;
    }
    return (status);
}