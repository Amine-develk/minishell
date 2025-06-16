NAME = minishell
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline -lncurses
INCLUDES = -Iincludes -Ilibft
LIBFT_DIR = includes/libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS =	src/builtins/cd.c src/builtins/echo.c src/builtins/env.c src/builtins/exit.c src/builtins/export.c src/builtins/pwd.c src/builtins/unset.c \
		src/execution/builtin_check.c src/execution/builtin_utils.c src/execution/cmd_path_utils.c src/execution/cmd_utils.c src/execution/exec_main.c src/execution/expansion.c src/execution/fds_utils.c src/execution/heredoc.c src/execution/redir_open.c src/execution/signals_handlers.c \
		src/main/minishell.c \
		src/tools/env_utils.c src/tools/mem_cleanup.c src/tools/shell_lvl.c \
		includes/get_next_line/get_next_line.c includes/get_next_line/get_next_line_utils.c

OBJS = ${SRCS:.c=.o}



all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

%.o: %.c includes/minishell.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: clean