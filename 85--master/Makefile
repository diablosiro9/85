EXEC		=	minishell

CC			=	gcc
RM			=	rm -rf
CFLAGS		=	-Wall -Werror -Wextra -g -fsanitize=address

LIBFT		=	lib/libft/libft.a

GNL			=	lib/gnl/get_next_line.c \
				lib/gnl/get_next_line_utils.c # Mimi - Faut aussi compiler les outils de get_next_line

SRCS		=	./src/main.c\
				./src/lexer/lexer.c ./src/lexer/tokenisateur.c ./src/lexer/tools_lexer.c\
				./src/lexer/split.c ./src/parsor/parsor.c ./src/parsor/check.c ./src/parsor/dollarz.c\
				./src/exec/exec.c ./src/exec/pipe.c ./src/exec/split.c ./src/exec/redir.c ./src/exec/here_doc.c ./src/exec/signal.c\
				./src/built_in/cd_exit.c ./src/built_in/env.c ./src/built_in/echo.c ./src/built_in/unset_pwd.c\
				./src/built_in/export.c ./src/built_in/help_export.c ./src/built_in/export_tools.c ./src/built_in/det_built.c\
				./src/utils/env.c ./src/utils/aff.c ./src/utils/list.c ./src/utils/str.c ./src/utils/free.c ./src/utils/get_env.c

OBJS		=	$(SRCS:.c=.o)

all: $(EXEC)

# Mimi - Tu executer ton minishell avec libft.a que tu avais compilé sur l'ordinateur de l'école
# mais vu que c'etait deux environement different, il y avait une imcompatibilité entre les deux
# Il faut que tu recompile ta libft a chaque fois que tu compile ton minishell, pareil pour les clean, fclean, re

$(EXEC): $(OBJS)
	make -C ./lib/libft 
	$(CC) $(CFLAGS) $(SRCS)  -lreadline -L/Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include/readline -o $(GNL) $(LIBFT) -o $(EXEC)
# -L/usr/local/lib -I/usr/local/include -lreadline -c
clean:
	make -C ./lib/libft clean
	$(RM) $(OBJS)

fclean: clean
	make -C ./lib/libft fclean
	$(RM) $(EXEC)

re: fclean all

.PHONY: all clean fclean re

# sudo apt-get install libreadline8
# sudo apt-get install libreadline-dev