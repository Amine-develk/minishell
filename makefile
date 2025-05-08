SRCS = minishell.c ft_split.c ft_substr.c ft_strcmp.c utils.c

OBJS = ${SRCS:.c=.o}

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

all: $(NAME)


$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) $(OBJSB)

fclean: clean
	@rm -f $(NAME) $(BONUS)

re: fclean all