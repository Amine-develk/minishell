NAME = minishell
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline -lncurses
LIBFT_DIR = includes/libft
LIBFT = $(LIBFT_DIR)/libft.a


SRCS = minishell.c utils.c
OBJS = ${SRCS:.c=.o}



all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

%.o: %.c minishell.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re