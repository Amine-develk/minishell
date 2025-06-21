NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -I ~/.brew/opt/readline/include -I ~/.brew/opt/ncurses/include
LDFLAGS = -L ~/.brew/opt/readline/lib -L ~/.brew/opt/ncurses/lib   -l readline -l ncurses
INCLUDES = -Iincludes -Ilibft
LIBFT_DIR = includes/libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = src/built_ins/builtin_utils.c src/built_ins/env.c \
		src/env/env.c src/env/shell_level.c \
		src/execution/error_handler.c \
		src/main/minishell.c src/main/signals.c \
		src/parsing/ambiguous.c src/parsing/errors.c src/parsing/ft_addstr.c \
		src/parsing/helper.c src/parsing/parsing.c src/parsing/redirection.c \
		src/parsing/tokenizer.c src/parsing/utils.c \
		src/utils/list_utils.c src/utils/free_mem.c
OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(LDFLAGS)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c includes/minishell.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all 

.PHONY: clean