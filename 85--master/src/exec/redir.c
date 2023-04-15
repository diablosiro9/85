#include "../../include/include.h"

int ft_redir_detec_right(t_list *str)
{
   int i = 0;
//    t_list *current = str;
	t_token	*current = g_data.token;
	(void)str;
	
	while (current != NULL)
   	{
    //   printf("-> %s\n", current->content);
      if (ft_strcmp(current->value, ">") == 0
         || ft_strcmp(current->value, ">>") == 0)
         i++;
      current = current->next;
   }
//    printf("-> DETECTED %d REDIR RIGHT\n", i);
   return (i);
}

int ft_redir_detec_left(t_list *str)
{
   int i = 0;
//    t_list *current = str;
   t_token	*current = g_data.token;
	(void)str;
   while (current->next != NULL)
   {
      if (ft_strcmp(current->value, "<") == 0)
      i++;
      current = current->next;
   }
   return (i);
}

int ft_redir_left(t_list *str) {
   (void)str;
   return 0;
}

// int redir_left(t_list *str) {
//    int fd;
//    int ret = 0;
//    char *filename;
//    char *command;
//    char buf[BUFSIZ];
//    char **argv = ft_exec_args(str);

//    filename = argv[2];
//    printf("filename = %s\n", filename);
//    command = argv[0];
//    printf("command = %s\n", command);

//    fd = open(filename, O_RDONLY);

//    if(fd == -1) {
//       printf("Erreur filename %s\n", filename);
//       exit(1);
//    }

//    int pipe_fd[2];
//    if (pipe(pipe_fd) == -1) {
//       printf("tube pt\n");
//       exit(1);
//    }

//    pid_t pid = fork();

//    if (pid == -1) {
//       printf("fils dead\n");
//       exit(1);
//    } else if (pid == 0) {
//       close(pipe_fd[0]); 
//       dup2(pipe_fd[1], STDOUT_FILENO);
//       close(pipe_fd[1]);
//       dup2(fd, STDIN_FILENO);
//       ret = read(fd, buf, BUFSIZ);
//       printf("fd = %d - ret = %d\n, ", fd, ret);
//       close(fd);
//       char *cmd[] = {get_cmd_file(command), NULL};
//       execve(get_cmd_file(command), cmd, get_env_bis(g_data.env));
//       exit(1);
//    } else {
//       close(pipe_fd[1]); 

//       while (1) {
//          int bytes_read = read(pipe_fd[0], buf, BUFSIZ); 
//          printf("LECTURE = %d\n", bytes_read);
//          if (bytes_read <= 0) break;
//          write(STDOUT_FILENO, buf, bytes_read); 
//       }
//       close(pipe_fd[0]); 
//       close(fd);
//       waitpid(pid, NULL, 0);
//    }
//    return 0;
// }




// int ft_redir_right(t_list *str) 
// {
//    int fd, status;
//    char *filename;
//    char *command;
//    char **argv = ft_exec_args(str);
//    char buf[MAX_BUF_SIZE];
//    pid_t pid;

//    filename = argv[2];
//    printf("filename = %s\n", filename);
//    command = argv[0];
//    printf("command = %s\n", command);

//    fd = open(filename, O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH); // ouvrir le fichier en écriture
//    printf("fd = %d\n", fd);
//    if(fd == -1) {
//       fd = open(filename, O_WRONLY | O_TRUNC);
//       if (fd == -1) {
//          fd = open(filename, O_RDWR); 
//          if (fd == -1) {
//             printf("Erreur filename1 %s\n", filename);
//             exit(1);
//          }
//       }
//    }

//    int pipe_fd[2]; 
//    if (pipe(pipe_fd) == -1) {
//       printf("tube pt1\n");
//       exit(1);
//    }

//    pid = fork(); 
//    printf("FILS = %d\n", pid);
//    if (pid == -1) {
//       printf("fils dead1\n");
//       exit(1);
//    } else if (pid == 0) { 
//       close(pipe_fd[0]); 
//       dup2(pipe_fd[1], STDOUT_FILENO);
//       close(pipe_fd[1]); 
//       char *cmd[] = {get_cmd_file(command), NULL};
//       execve(get_cmd_file(command), cmd, get_env_bis(g_data.env)); 
//       exit(1);
//    } else { 
//       close(pipe_fd[1]); 

//       while (1) {
//          int bytes_read = read(pipe_fd[0], buf, MAX_BUF_SIZE); 
//          if (bytes_read <= 0) break;
//          write(fd, buf, bytes_read); 
//       }

//       close(pipe_fd[0]); 
//       close(fd); 

//       waitpid(pid, &status, 0); 
//    }

//    return 0;
// }


// char *ft_redir_rigth_file(t_token *token)
// {
//    t_token *tmp = token;

//    while (tmp && tmp->t_type != REDIR) {
//       tmp = tmp->next;
//    }
//    return tmp->next->value;
// }

// int ft_redir_right_exec(t_token cmd, char **argv, char *file)
// {
   
//    printf("EXEC CMD = %s | %u\n", cmd.value, cmd.t_type);
//    for (int i = 0; argv[i]; i++) {
//       printf("argv[%d] = %s\n", i, argv[i]);
//    }
//    printf("file = %s\n", file);

//    int fds[2];
//    int status = 0;
//    pid_t pid = 0;
//    static int file_fd = 0;

//    if (access(file, F_OK | R_OK) == 0 && (file_fd = open(file, O_WRONLY | O_TRUNC | O_RDONLY)) == -1)
//       perror("open");
//    else if ((file_fd = open(file, O_CREAT | O_WRONLY, 0644)) == -1)
//       perror("open");
//    pipe(fds);
//    if ((pid = fork()) == -1)
//       perror("fork");
//    else if (pid == 0) {
//       dup2(fds[0], STDIN_FILENO);
//       dup2(fds[1], STDOUT_FILENO);
//       dup2(file_fd, STDOUT_FILENO);
//       if (execve(cmd.value, argv, get_env_bis(g_data.env)) == -1) {
//          perror("execve");
//          exit(EXIT_FAILURE);
//       }
//    }
//    else {
//       waitpid(pid, &status, 0);
//       if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
//          close(fds[0]);
//          close(fds[1]);
//          close(file_fd);
//          return WEXITSTATUS(status);
//       }
//    }
//    close(fds[0]);
//    close(fds[1]);
//    close(file_fd);
//    return 0;
// }

int   ft_redir_argv_size(t_token *token)
{
   int   size = 0;
   t_token *tmp = token;

   while (tmp && tmp->t_type != REDIR) {
      tmp = tmp->next;
      size += 1;
   }
   return size;
}

char  **ft_redir_argv(t_token **token)
{
   int idx = 0;
   char **argv = NULL;
   int size = ft_redir_argv_size(*token);
   
   if (!(argv = malloc(sizeof(char *) * (size + 1))))
      return NULL;
   while (token && (*token)->t_type != REDIR && (*token)->t_type != RREDIR) {
      argv[idx] = ft_strdup((*token)->value);
      *token = (*token)->next;
      idx += 1;
   }
   argv[idx] = NULL;
   return argv;
}

int ft_redir_file(char *file, int r_type)
{
   int fd = 0;

   if (access(file, F_OK | R_OK) == 0) {
      if ((r_type == REDIR && (fd = open(file, O_WRONLY | O_RDONLY | O_TRUNC)) == -1)
         || (r_type == RREDIR && (fd = open(file, O_WRONLY | O_RDONLY | O_APPEND)) == -1))
         perror("open");
   }
   else if ((fd = open(file, O_CREAT | O_WRONLY, 0644)) == -1)
      perror("open");
   return (fd);
}

int ft_redir_exec(int fd, char **argv)
{
   int fds[3];
   int status = 0;
   pid_t pid = 0;

   pipe(fds);
   if ((pid = fork()) == -1)
      perror("fork");
   else if (pid == 0) {
      dup2(fds[0], STDIN_FILENO);
      dup2(fds[1], STDOUT_FILENO);
      dup2(fd, STDOUT_FILENO);
      if (execve(argv[0], argv, get_env_bis(g_data.env)) == -1) {
         perror("execve");
         exit(EXIT_FAILURE);
      }
   }
   else {
      waitpid(pid, &status, 0);
      if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
         close(fds[0]);
         close(fds[1]);
         close(fd);
         return WEXITSTATUS(status);
      }
   }
   close(fds[0]);
   close(fds[1]);
   close(fd);
   return 0;
}


int ft_redir_right(t_list *list)
{
   int fd = 0;
   int idx = 0;
   int type = 0;
   char **argv = NULL;
   g_data.list = list;
   t_token *tmp = g_data.token;

//    printf("-------> REDIR RIGHT\n");

   if (tmp->t_type == REDIR || tmp->t_type == RREDIR) {
      if (tmp->next == NULL) {
         printf("minishell: syntax error near unexpected token `newline'\n");
         g_data.exit = 258;
         return (258);
      }
	  printf("al\n");
      ft_redir_file(tmp->next->value, tmp->t_type);
      return (0);
   }
   argv = ft_redir_argv(&tmp);
   while (tmp) {
     
      if (tmp->t_type == REDIR || tmp->t_type == RREDIR) {
		printf("uuiii\n");
         type = tmp->t_type;
         idx += 1;
      }
      	if (tmp->t_type == WORD) {
         fd = ft_redir_file(tmp->value, type);
         if (idx == ft_redir_detec_right(list))
            ft_redir_exec(fd, argv);
      }
      tmp = tmp->next;
   }
   return (0);
}